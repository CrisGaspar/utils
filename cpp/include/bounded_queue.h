#include <vector>
#include <cstdint>
#include <cinttypes>
#include <stdexcept>


namespace efficient {
    const int32_t INVALID_INDEX = -1;
    const uint32_t QUEUE_MAX_SIZE_DEFAULT = 1024 * 1024;

    // Efficient bounded queue implementation with composable/chainable functional application
    // NOTE: This is not thread-safe. Use SynchronizedQueue for thread-safety.
    template<class T>
    class bounded_queue {
        T* data;
        int32_t first = INVALID_INDEX;
        int32_t last = INVALID_INDEX;
        uint32_t maxSize = QUEUE_MAX_SIZE_DEFAULT;

        /**
         * Updates the first and last indices to make room for a new element.
        */
        void updateIndicesForNewElement() {
            if (size() == maxSize) {
                // no room left
                throw std::logic_error("BoundedQueue: No room for new element. Already at max capacity");
            }

            if (first == INVALID_INDEX) {
                // previously empty queue
                first = last = 0;
            }
            else {
                // wrap around from buffer end to start if needed
                last = (last + 1) % maxSize;
            }
        }

     public:
        bounded_queue(const uint32_t queueMaxSize = QUEUE_MAX_SIZE_DEFAULT) : maxSize(queueMaxSize) {  data = new T[queueMaxSize]; }
        ~bounded_queue() { delete[] data; }

        int32_t size() const {
            if (first == INVALID_INDEX || last == INVALID_INDEX) {
                return 0;
            }

            // 2 cases: no-wrap and wrap-around-buffer-end
            return (last >= first) ? (last - first) + 1 : (maxSize - first) + (last + 1);
        }

        /**  
         * Push new element: move-element version
        */
        void push(T&& elem) {
            updateIndicesForNewElement();
            data[last] = std::move(elem);
        }

        /** 
         * Push new element: copy-element version 
        */
        void push(const T& elem) {
            updateIndicesForNewElement();
            data[last] = elem;
        }

        /**
         * Pop oldest element
        */
        T pop() {
            int32_t queueSize = size();
            if (queueSize == 0) {
                throw std::logic_error("BoundedQueue: Nothing to pop. Empty queue!");
            }

            // Oldest elemnent is the first one.
            int32_t index = first;
            if (queueSize == 1)
            {
                // To empty queue reset indices to invalid state
                first = last = INVALID_INDEX;
            }
            else {
                // wrap around from buffer end to start if needed
                first = (first + 1) % maxSize;
            }

            // Use move semantics to return the element
            return std::move(data[index]);
        }


        /**
         * Remove all elements from queue
        */
        void clear() {
            while(first != INVALID_INDEX) {
                pop();
            }
        }

        /**
         * Applies given function to each element and returns a reference to the modified queue.
         * NOTE: If the queue is empty, no exception is thrown. Reference to self is returned to allow chaining to continue.
         */
        template<class UnaryFunction>
        bounded_queue<T>& operator()(UnaryFunction f) {
            if (size() == 0) {
                // Empty queue: nothing to apply. Return reference to self as is.
                return *this;
            }

            // Apply function to each element. Wrap around from buffer end to start if needed.
            // Stop loop when we reach the last element.
            for (int32_t index = first; index != last; index = (index + 1) % maxSize) {
                f(data[index]);
            }

            // Apply function to last element
            f(data[last]);
            
            // Return reference to self for chaining
            return *this;
        }
    };
}
