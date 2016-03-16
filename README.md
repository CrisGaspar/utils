# utils
Utilities
* C++:
  - bounded_queue.h: cache-efficient implementation using array + composable function applications
  - syncronized_queue.h: bounded_queue that is synchronized
  - queue_test.cpp: tests 
  - queue_test_perf.cpp: performance test comparing against std::queue
  - synchronized_queue_test.cpp: test with multiple threads using the synchronized queue:
    clang++ -std=c++11 -pthread synchronized_queue_test.cpp
