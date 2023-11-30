cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UtilsTests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the GoogleTest package
find_package(GTest REQUIRED)

# Add the executable
add_executable(BoundedQueueTest cpp/tests/bounded_queue_test.cpp)
add_executable(SynchronizedQueueTest cpp/tests/synchronized_queue_test.cpp)

# Enable testing
enable_testing()

# Add the test
add_test(NAME BoundedQueueTest COMMAND BoundedQueueTest)
add_test(NAME SynchronizedQueueTest COMMAND SynchronizedQueueTest)

# Link the GoogleTest and pthread library to the executable
target_link_libraries(BoundedQueueTest GTest::GTest GTest::Main pthread)
target_link_libraries(SynchronizedQueueTest GTest::GTest GTest::Main pthread)