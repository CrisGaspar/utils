#include <iostream>
#include "bounded_queue.h"

using namespace efficient;

/* Tests bounded queue functionlity */
int main(int argc, char** argv) {
    bounded_queue<int> q;

    int count = 3;
    for (int i = 0; i < 2 * count; ++i) {
        q.push(i);
    }

    for (int i = 0; i < 2 * count; ++i) {
        cout << q.pop() << " ";
    }
    cout << endl;

    auto coutf = [](int32_t& n) { cout << n << " "; };
    q(coutf);
    cout << endl;

    for (int i = 0; i < 2 * count; ++i) {
        q.push(i);
        q.push(2*i);
        q.push(3*i);
        cout << q.pop() << " ";
    }
    cout << endl;

    auto doubleit = [](int32_t& n) { n = 2 * n; };
    auto dec = [](int32_t& n) { --n; };

    cout << "Queue size: " << q.size() << endl;
    cout << "Queue contents: " << endl;

    /*
    ** NOTE: This is pretty cool!
    ** Chained Function Application
    */
    q(coutf)(doubleit)(dec);
    cout << endl;

    cout << "Queue contents: " << endl;
    q(coutf);
    cout << endl;

    int curPop = q.pop();
    cout << "Queue: popped element " << curPop << endl;

    try {
        for (int i = 0; i < QUEUE_MAX_SIZE_DEFAULT + 1; ++i) {
            q.push(i);
        }
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
