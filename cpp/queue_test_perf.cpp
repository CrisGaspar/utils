#include <iostream>
#include <chrono>
#include <queue>
#include "bounded_queue.h"

using namespace efficient;

int main(int argc, char** argv) {
    bounded_queue<int> q;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_SIZE; ++i) {
        q.push(i);
    }
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "Bounded queue took " << microseconds << " microseconds to push " << MAX_SIZE << " elements" << endl;

    start = std::chrono::high_resolution_clock::now();
    q.clear();
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "Bounded queue took " << microseconds << " microseconds to clear" << endl;

    std::queue<int> sq;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_SIZE; ++i) {
        sq.push(i);
    }
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "STL queue took " << microseconds << " microseconds to push " << MAX_SIZE << " elements" << endl;

    start = std::chrono::high_resolution_clock::now();
    while (!sq.empty()) {
        sq.pop();
    }
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout << "STL queue took " << microseconds << " microseconds to clear" << endl;
}
