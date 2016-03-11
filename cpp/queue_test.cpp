#include <iostream>
#include "queue.h"

using namespace efficient;

int main(int argc, char** argv) {
    int count = 100;
    queue<int> q(count);

    for (int i = 0; i < 2 * count; ++i) {
        q.enqueue(i);
    }

    for (int i = 0; i < 2 * count; ++i) {
        cout << q.dequeue() << " ";
    }
    cout << endl;

    auto coutf = [](int32_t& n) { cout << "n=" << n << " "; };
    q(coutf);
    cout << endl;

    for (int i = 0; i < 2 * count; ++i) {
        q.enqueue(i);
        q.enqueue(2*i);
        q.enqueue(3*i);
        cout << q.dequeue() << " ";
    }
    cout << endl;

    cout << "Queue size: " << q.size() << endl;
    q(coutf);
    cout << endl;
    return 0;
}
