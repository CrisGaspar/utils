#include <vector>
#include <cstdint>
#include <cinttypes>
#include <stdexcept>

using namespace std;

namespace efficient {
    const int32_t INVALID_IDX = -1;
    const uint32_t MAX_SIZE = 1024 * 1024;

    // Bounded queue with composable/chainable functional application
    template<class T>
    class bounded_queue {
        T* data;
        int32_t first = INVALID_IDX;
        int32_t last = INVALID_IDX;
        uint32_t maxsz = MAX_SIZE;

        void push_util() {
            if (size() == maxsz) {
                // cannot accomodate
                throw logic_error("BoundedQueue: already at max capacity");
            }

            if (first == INVALID_IDX) {
                // previously empty
                first = last = 0;
            }
            else {
                last = (last + 1) % maxsz;
            }
        }

     public:
        bounded_queue(const uint32_t max = MAX_SIZE) : maxsz(max) {  data = new T[maxsz]; }
        ~bounded_queue() { delete[] data; }

        int32_t size() const {
            if (first == INVALID_IDX || last == INVALID_IDX) {
                return 0;
            }

            return (last >= first) ? (last - first) + 1 : (maxsz - first) + (last + 1);
        }

        void push(T&& elem) {
            push_util();
            data[last] = move(elem);
        }

        void push(const T& elem) {
            push_util();
            data[last] = elem;
        }

        T pop() {
            int32_t qSize = size();
            if (qSize == 0) {
                throw logic_error("Queue: can't pop empty queue!");
            }

            int32_t idx = first;
            if (qSize == 1)
            {
                first = last = INVALID_IDX;
            }
            else {
                first = (first + 1) % maxsz;
            }

            return move(data[idx]);
        }

        void clear() {
            while(first != INVALID_IDX) {
                pop();
            }
        }

        // Application of composable functions
        template<class UnaryFunction>
        bounded_queue<T>& operator()(UnaryFunction f) {
            if (size() == 0) {
                // Empty queue: nothing to apply!
                return *this;
            }

            for (int32_t i = first; i != last; i = (i + 1) % maxsz) {
                f(data[i]);
            }
            f(data[last]);
            return *this;
        }
    };
}
