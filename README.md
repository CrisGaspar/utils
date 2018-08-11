# utils
Utilities

* C++
  - bounded_queue.h: cache-efficient implementation using array. Has chainable functions support.
  - bst.h: node-based binary search tree implementation with a twist: the element type T can specify
    what Key type is to be used for comparisons. Keys are computed on create/insert/find/delete operations.
  - bst_test.cpp: functional test for binary search tree: both primitive type (int) and custom type (eg: Spaceship class)
  - queue_test.cpp: functional tests for queue
  - queue_test_perf.cpp: performance test comparing against std::queue
  - syncronized_queue.h: synchronized bounded queue. Clients specify the Mutex type they need.
  - synchronized_queue_test.cpp: multiple threads using the synchronized queue
    clang++ -std=c++14 -pthread -g synchronized_queue_test.cpp -o synchronized_queue_test
  - value-semantics.cpp: implementation by Adobe of a container of heterogenenous objects - useful for full undo functionality

* Scala
  - proxy.scala: connects to a source S via TCP and forwards all packets received
    from S to all of its currently connected clients

