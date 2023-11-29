#include <iostream>
#include "bounded_queue.h"

using namespace efficient;
using namespace std;

/* Tests for bounded queue implementation */
int main(int argc, char** argv) {
    bounded_queue<int> queue;

    int count = 3;
    for (int index = 0; index < 2 * count; ++index) {
        queue.push(index);
    }

    for (int index = 0; index < 2 * count; ++index) {
        cout << queue.pop() << " ";
    }
    cout << endl;

    /** Print function to be applied to elements in the queue */
    auto printFunc = [](int32_t& value) { cout << value << " "; };

    queue(printFunc);
    cout << endl;

    for (int index = 0; index < 2 * count; ++index) {
        queue.push(index);
        queue.push(2*index);
        queue.push(3*index);
        cout << queue.pop() << " ";
    }
    cout << endl;

    /** Function to double a given value*/
    auto doubleFunc = [](int32_t& value) { value = 2 * value; };

    /** Function to decrement by 1 the given value*/
    auto decrementFunc = [](int32_t& value) { --value; };

    cout << "Queue size: " << queue.size() << endl;
    cout << "Queue contents: " << endl;

    /*
    ** Apply a series of functions to each element in the queue.
    */
    queue(printFunc)(doubleFunc)(decrementFunc);
    cout << endl;

    cout << "Queue contents: " << endl;
    queue(printFunc);
    cout << endl;

    int poppedValue = queue.pop();
    cout << "Queue: popped element " << poppedValue << endl;

    try {
        for (int index = 0; index < QUEUE_MAX_SIZE_DEFAULT + 1; ++index) {
            queue.push(index);
        }
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
