# utils
Utilities
* C++:
  - bounded_queue.h: cache-efficient implementation using array + composable function applications
  - syncronized_queue.h: synchronized bounded_queued
  - queue_test.cpp: functional tests for queue
  - queue_test_perf.cpp: performance test comparing against std::queue
  - synchronized_queue_test.cpp: test with multiple threads using the synchronized queue
    clang++ -std=c++11 -pthread synchronized_queue_test.cpp
  - bst.h: standard binary search tree implementation with a twist: the element type T can specify
    what Key type is to be used for comparisons. Keys are not stored. They are computed on
    create/insert/find/delete operations.
  - bst_test.cpp: functional test for binary search tree: both primitive type (int) and custom type (eg: Spaceship class)
