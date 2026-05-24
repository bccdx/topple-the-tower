cmake_minimum_required(VERSION 3.10)
project(ToppleTheTower)
 
set(CMAKE_CXX_STANDARD 11)
 
# Enable testing
enable_testing()

# game logic. linked by both the game and the tests
add_library(topple_logic
    src/Counter.cpp
    src/Card.cpp
)

# Tell the compiler where to find header files
target_include_directories(topple_logic PUBLIC include)
 
# Main executable
add_executable(topple_game src/main.cpp)
target_link_libraries(topple_game topple_logic)
 
# Test executable
add_executable(run_tests tests/test_counter.cpp)
target_link_libraries(run_tests topple_logic)
 
# Register with CTest
add_test(NAME ToppleTests COMMAND run_tests)