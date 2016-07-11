#include <iostream>
#include <mutex>
#include <thread>
#include "synchronized_queue.h"

using namespace efficient;

int main(int argc, char** argv) {
    SynchronizedQueue<int, mutex> queue;

    auto playWithQueue = [&queue] () {
        for (int i = 0; i < 10000; ++i) {
            queue.enqueue(i);
            queue.enqueue(2*i);
            queue.dequeue();
        }
    };

    uint32_t threadNum = 10;
    vector<thread> threads;
    threads.reserve(threadNum);
    for (int j = 0; j < threadNum; ++j) {
        threads[j] = thread(playWithQueue);
    }

    for (int j = 0; j < threadNum; ++j) {
        threads[j].join();
    }
    cout << "Threads finished! Queue contents" << endl;

    auto coutf = [](int32_t& n) { cout << n << " "; };
    queue(coutf);
    cout << endl;
    return 0;
}
