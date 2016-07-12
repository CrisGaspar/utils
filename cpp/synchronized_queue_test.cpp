#include <iostream>
#include <mutex>
#include <thread>
#include "synchronized_queue.h"

using namespace efficient;

int main(int argc, char** argv) {
    SynchronizedQueue<int, mutex> queue;

    // Use a lambda function to define the operations performed on the same
    // queue by each thread separately
    auto playWithQueue = [&queue] () {
        for (int i = 0; i < 10000; ++i) {
            // Perform a few queue operations
            queue.enqueue(i);
            queue.enqueue(2*i);
            queue.dequeue();
        }
    };

    uint32_t threadNum = 10;
    vector<thread> threads;
    threads.reserve(threadNum);
    for (int j = 0; j < threadNum; ++j) {
        // Setup each thread to execute the lamba function that performs the
        // queue operations
        threads[j] = thread(playWithQueue);
    }

    for (int j = 0; j < threadNum; ++j) {
        threads[j].join();
    }
    cout << "Threads finished! Queue contents" << endl;

    // Create lambdas: to print an integer, to double an integer
    auto coutf = [](int32_t& n) { cout << n << " "; };
    auto doubleIt = [](int32_t&n) { n *= 2; };

    // Double the value of each queue item and output the final state.
    // Lambdas are applied to each item using the overloaded operator().
    queue(doubleIt)(coutf);
    cout << endl;
    return 0;
}
