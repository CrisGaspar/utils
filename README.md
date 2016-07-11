# utils
Utilities

* C++
  - array_bst.h: cache-efficient array-based binary search tree implementation
  - bounded_queue.h: cache-efficient implementation using array. Has chainable functions support.
  - bst.h: node-based binary search tree implementation with a twist: the element type T can specify
    what Key type is to be used for comparisons. Keys are computed on create/insert/find/delete operations.
  - bst_test.cpp: functional test for binary search tree: both primitive type (int) and custom type (eg: Spaceship class)
  - kDistanceDuplicates.cpp: finding matrix duplicates that are at most k positions apart
  - matrixRotation.cpp: rotate a matrix clockwise by 1 position for each element
  - queue_test.cpp: functional tests for queue
  - queue_test_perf.cpp: performance test comparing against std::queue
  - syncronized_queue.h: synchronized bounded queue. Clients specify the Mutex type they need.
  - synchronized_queue_test.cpp: multiple threads using the synchronized queue
    clang++ -std=c++14 -pthread -g synchronized_queue_test.cpp -o synchronized_queue_test
  - value-semantics.cpp: Adobe implementation of a container of hetergenenous objects - useful for full undo functionality

* Scala
  - proxy.scala: connects to a source S via TCP and forwards all packets received
    from S to all of its currently connected clients

* Ruby
  - todo.rb: TODO app
  - tree.rb: binary search tree implementation

* Python
  - tictactoe.py: n x n TicTacToe game
  - test_ticTacToe.py: TicTacToe unit tests - full coverage
  - supermarket.py: basic checkout with laddered price discounts
  - test_product.py and test_checkout.py: unit tests
  - cryptoparser.py: HTTP crypto header parser

* Java
  - TicTacToe.java: best move implementation
  - Parentheses.java: checks if parentheses in a string are balanced

Exercises
* C++: cpp/exercises
  - filter.cpp: simple filtering example using lambdas
  - rover.*: rover game implementation: 2D integer grid navigation with simple 'f' forward, 'l' turn-left, and 'r' turn-right commands
    Usage: rover2 <-t filename> | Use -t filename to run in test mode on the given file. Use no parameters to run interactive mode
* Python: python/exercises
  - balanced.py: balanced parentheses checker
  - closestRGB.py: RGB closest base color (RGB+Black+White) finder  
  - compress.py: length-based string encoding
  - rover.py: rover implementation
  - test_rover.py and rover_functional*.py: rover tests
  - mergesort.py and test_mergesort.py


