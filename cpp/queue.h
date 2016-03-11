#include <vector>
#include <cstdint>
#include <cinttypes>
#include <stdexcept>

using namespace std;

namespace efficient {
    template<class T>
    class queue {
        const int32_t INVALID_IDX = -1; 
        vector<T> data;
        int32_t first;
        int32_t last;

     public:
        // Default initialize n elements
        queue(size_t n): data(n), first(INVALID_IDX), last(INVALID_IDX) {}
        
        int32_t size() const { 
            if (first == INVALID_IDX || last == INVALID_IDX) {
                return 0;
            }

            return (last >= first) ? (last - first) + 1 : (data.size() - first) + (last + 1);  }

        void enqueue(T elem) {
            if (size() == data.capacity()) {
                // need to expand vector: double capacity
                vector<T> newV;
                newV.reserve(data.size() * 2);

                if (last >= first) {
                    newV.insert(newV.begin(), data.begin() + first, data.begin() + last + 1);
                } else {
                    newV.insert(newV.begin(), data.begin() + first, data.end());
                    newV.insert(newV.end(), data.begin(), data.begin() + last + 1);
                }
                data = std::move(newV);
                first = 0;
                last = data.size() - 1; 
                data[++last] = move(elem);
                return;
            }

            if (first == INVALID_IDX) {
                // previously empty
                first = last = 0;
            }
            else {
                last = (last + 1) % data.capacity();            
            }

            data[last] = elem;
        }

        T dequeue() {
            int32_t qSize = size();
            if (qSize == 0) {
                throw logic_error("Queue: can't dequeue empty queue!");
            }

            T val = data[first];
            if (qSize == 1)
            {
                first = last = INVALID_IDX;
            }
            else { 
                first = (first + 1) % data.capacity();            
            }
            return val;
        }

        void clear() {
            data.clear();
            first = last = INVALID_IDX;
        }

        // Application of composable functions
        template<class UnaryFunction>
        queue<T> operator()(UnaryFunction f) {
            int32_t qSize = size();
            if (qSize == 0) {
                cout << "Empty queue: nothing to apply!" << endl;
                return *this;
            }

            for (int32_t i = first; i != last; i = (i + 1) % qSize) {
                f(data[i]);
            }
            return *this;
        }
    };
}
