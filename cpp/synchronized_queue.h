#include <vector>
#include <cstdint>
#include <cinttypes>
#include <stdexcept>

using namespace std;

namespace efficient {
    const int32_t INVALID_IDX = -1; 
    const uint32_t MAX_SIZE = 1024 * 1024;

    // Synchronized bounded queue with composable/chainable functional application
    template<class T, class Lock>
    class synchronized_queue {
        T* data;
        Lock l;
        typedef lock_guard<Lock> LockGuard;
        int32_t first = INVALID_IDX;
        int32_t last = INVALID_IDX;
        uint32_t maxsz = MAX_SIZE;
        int32_t sz = 0;

        void push_util() {
            if (sz == maxsz) {
                // cannot accomodate
                throw logic_error("SynchronizedQueue: already at max capacity");
            }

            if (first == INVALID_IDX) {
                // previously empty
                first = last = 0;
            }
            else {
                last = (last + 1) % maxsz;            
            }
            ++sz;
        }

     public:
        synchronized_queue(const uint32_t max = MAX_SIZE) : maxsz(max) {  data = new T[maxsz]; }
        ~synchronized_queue() { delete[] data; }
     
        int32_t size() const { 
            return sz;
        }
        
        void push(T&& elem) {
            LockGuard g(l);
            push_util();
            data[last] = move(elem);
        }

        void push(const T& elem) {
            LockGuard g(l);
            push_util();
            data[last] = elem;
        }


        T pop() {
            if (sz == 0) {
                throw logic_error("Queue: can't pop empty queue!");
            }

            int32_t idx = first;
            if (sz == 1)
            {
                first = last = INVALID_IDX;
            }
            else { 
                first = (first + 1) % maxsz;            
            }
            --sz;

            return move(data[idx]);
        }

        void clear() {
            while(first != INVALID_IDX) { 
                pop();
            }
        }

        // Application of composable functions
        template<class UnaryFunction>
        synchronized_queue<T, Lock>& operator()(UnaryFunction f) {
            if (sz == 0) {
                cout << "Empty queue: nothing to apply!" << endl;
                return *this;
            }

            LockGuard g(l);
            for (int32_t i = first; i != last; i = (i + 1) % maxsz) {
                f(data[i]);
            }
            f(data[last]);
            return *this;
        }
    };
}
