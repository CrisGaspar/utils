# utils
Utilities

* C++
  - bounded_queue.h: cache-efficient implementation using array. Has chainable functions support.
  - syncronized_queue.h: synchronized bounded queue. Clients specify the Mutex type they need.
  - queue_test.cpp: functional tests for queue
  - queue_test_perf.cpp: performance test comparing against std::queue
  - synchronized_queue_test.cpp: multiple threads using the synchronized queue
    clang++ -std=c++11 -pthread synchronized_queue_test.cpp
  - bst.h: node-based binary search tree implementation with a twist: the element type T can specify
    what Key type is to be used for comparisons. Keys are not stored. They are computed on
    create/insert/find/delete operations.
  - bst_test.cpp: functional test for binary search tree: both primitive type (int) and custom type (eg: Spaceship class)
  - array_bst.h: cache-efficient array-based binary search tree implementation

* Scala
  - proxy.scala: connects to a source S via TCP and forwards all packets received
    from S to all of its currently connected client

* Ruby
  - tree.rb: binary search tree implementation

Exercises
* C++: cpp/exercises
  - rover.*: rover game implementation: 2D integer grid navigation with simple 'f' forward, 'l' turn-left, and 'r' turn-right commands
    Usage: rover2 <-t filename> | Use -t filename to run in test mode on the given file. Use no parameters to run interactive mode
