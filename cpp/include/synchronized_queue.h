#include <vector>
#include <cstdint>
#include <cinttypes>
#include <stdexcept>
#include <memory>

using namespace std;

namespace efficient {
    const int32_t INVALID_INDEX = -1;
    const uint32_t QUEUE_MAX_SIZE_DEFAULT = 1024 * 1024;

    // Synchronized bounded queue with composable/chainable functional application
    // The 2 type parameters are: 
    // 1. type T of the elements in the queue
    // 2. type Lock of the mutex used to synchronize access to the queue
    template<class T, class Lock>
    class SynchronizedBoundedQueue {
    private:
        unique_ptr<T[]> mData;  ///< fixed sized array that holds the queue items
                                // Fixed size is used to maximize cache efficiency
                                // hence guaranteeing very fast enqueue/dequeue
        Lock mLock;             ///< mutex for synchronized access to the queue

        // Using STL lock_guard to achieve RAII with mutex
        typedef lock_guard<Lock> LockGuard;

        // We keep track of the beginning and end of the queue with mFirstIndex
        // and mLastIndex.
        // The mData array is pre-allocated and is used in a circular fashion meaning
        // the indices wrap-arround past end and beginning if necessary
        // e.g: if maximum size was 3 and we enqueue 2, 3, 1,  dequeue, then enqueue 5
        // the final array would be:
        // 5, 3, 1 with mFirstIndex = 1 and mLastIndex = 0
        int32_t mFirstIndex = INVALID_INDEX;
        int32_t mLastIndex = INVALID_INDEX;
        int32_t mSize = 0;      ///< current size of the queue
        int32_t mMaxSize = 0;   ///< maximum size of the queue

        /*
         * Enqueue helper method
         * NOTE: Assumes lock is already acquired before calling this method
         */
        void enqueue_nolock() {
            if (mSize == mMaxSize) {
                // cannot accomodate new element
                throw logic_error("SynchronizedBoundedQueue: already at max capacity");
            }

            if (mFirstIndex == INVALID_INDEX) {
                // previously empty queue
                mFirstIndex = mLastIndex = 0;
            }
            else {
                // increment last index wrapping around the end
                mLastIndex = (mLastIndex + 1) % mMaxSize;
            }
            ++mSize;
        }

        /**
         * Dequeue helper method.
         * NOTE: Assumes lock is already acquired before calling this method
        */
        T dequeue_nolock() {
            if (mSize == 0) {
                throw logic_error("SynchronizedBoundedQueue: Nothing to pop. Empty queue");
            }

            int32_t index = mFirstIndex;
            if (mSize == 1) {
                // 1 element in queue, reset the indices to invalid value
                mFirstIndex = mLastIndex = INVALID_INDEX;
            }
            else {
                // increment first index wrapping around the end
                mFirstIndex = (mFirstIndex + 1) % mMaxSize;
            }
            --mSize;

            // Use STL move to steal this reference and void copying the element
            return std::move(mData[index]);
        }

     public:
        /*
         * Constructor can optionally load a batch of items in the intial queue.
         * e.g.: copying a queue's data to perform other actions on the same items
         * auto copies = otherQueue.clone();
         * SynchronizedQueue copiesQueue(copies);
         */
        SynchronizedBoundedQueue(
                const uint32_t maxSize = QUEUE_MAX_SIZE_DEFAULT,
                const vector<T>& items = vector<T>()
                ) : mMaxSize(maxSize) {
            mData = make_unique<T[]>(mMaxSize);
            for (const auto& item: items) {
                enqueue(item);
            }
        }

        ~SynchronizedBoundedQueue() { clear(); }

        /*
         * Delete copy and move constructor and assignment.
         * This is to avoid deadlocks.
         * Any of these operations would have to acquire both the lock of the
         * left-hand-side object and right-hand-side objects.
         * If 2 different threads are executing each:
         * q1 = q2
         * and
         * q2 = q1
         * Deadlock would occur as each would hold its own lock and block on
         * the other's lock indefinitely
         *
         * If the items need to be copied use the clone() method
         * below to get a vector<T> of item copies and use the regular constructor
         * auto copies = otherQueue.clone();
         * SynchronizedQueue copiesQueue(copies);
         *
         */

        // copy constructor
        SynchronizedBoundedQueue(const SynchronizedBoundedQueue<T, Lock>& other) = delete;
        // move constructor
        SynchronizedBoundedQueue(SynchronizedBoundedQueue<T, Lock>&& other) = delete;

        // copy assignment
        SynchronizedBoundedQueue& operator=(SynchronizedBoundedQueue<T, Lock>& other) = delete;
        // move assignment
        SynchronizedBoundedQueue& operator=(SynchronizedBoundedQueue<T, Lock>&& other) = delete;

        /*
         * Clone returns a vector of copies of the items in the queue
         */
        vector<T> clone() {
            vector<T> copiedValues;
            // Create an anonymous function to insert into copied Values and
            // apply it to all items in queue via overloaded operator() which uses is synchronized via lock
            this->operator()([&copiedValues](const T& item) { copiedValues.push_back(item); });
            return copiedValues;
        }

        int32_t size() const {
            return mSize;
        }

        /*
         *  Enqueues an element by moving it which avoids copying it
        */
        void enqueue(T&& elem) {
            LockGuard guard(mLock);
            enqueue_nolock();

            // Use STL move to steal the contents of the rvalue and avoid copying
            mData[mLastIndex] = std::move(elem);
        }

        /** Enqueues an element by copying it*/
        void enqueue(const T& elem) {
            LockGuard guard(mLock);
            enqueue_nolock();
            mData[mLastIndex] = elem;
        }

        /**
         *  Removes the oldest element from the queue
        */
        T dequeue() {
            LockGuard guard(mLock);
            return dequeue_nolock();
        }

        /*
         * Removes all elements from the queue
         */
        void clear() {
            LockGuard guard(mLock);
            while(size() != 0) {
                dequeue_nolock();
            }
        }


        /** Non-const array[x] operator*/
        T& operator[](size_t index) {
            LockGuard guard(mLock);
            if (index >= size()) {
                throw out_of_range("Index out of range");
            }
            return mData[(mFirstIndex + index) % mMaxSize];
        }

        /** Const array[x] operator*/
        const T& operator[](size_t index) const {
            LockGuard guard(mLock);
            if (index >= size()) {
                throw out_of_range("Index out of range");
            }
            return mData[(mFirstIndex + index) % mMaxSize];
        }

        /*
         * Overload operator() to support application of composable functions
         * that are applied to each element in the queue
         * E.g: func could be a cout-like lambda function that prints the element it is given
         * Returns this queue to allow calls to be composed
         * e.g: queue(f1)(f2) which would apply function f1 to all elements
         * then apply function f2 to all elements
         */
        template<class UnaryFunction>
        SynchronizedBoundedQueue<T, Lock>& operator()(UnaryFunction func) {
            LockGuard guard(mLock);
            if (mSize == 0) {
                // Don't throw. Return this queue to allow calls to be composed
                return *this;
            }
            for (int32_t index = mFirstIndex; index != mLastIndex; index = (index + 1) % mMaxSize) {
                func(mData[index]);
            }

            // Apply function to last element as a separate step
            // Necessary since the queue uses the mData array in a circular fashion
            func(mData[mLastIndex]);

            // Return this queue to allow calls to be composed
            return *this;
        }
    };
}
