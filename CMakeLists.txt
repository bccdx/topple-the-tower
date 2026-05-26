cmake_minimum_required(VERSION 3.10)
project(ToppleTheTower)
 
set(CMAKE_CXX_STANDARD 11)
 
# Enable testing
enable_testing()

# game logic. linked by both the game and the tests
add_library(topple_logic
    src/Counter.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Character.cpp
    src/Hero.cpp
    src/Ironknight.cpp
    src/Strike.cpp
    src/Defend.cpp
    src/Bash.cpp
    src/IronWave.cpp
    src/Cleave.cpp
    src/PommelStrike.cpp
    src/ShrugItOff.cpp
    src/Clothesline.cpp
    src/TwinStrike.cpp
    src/Thunderclap.cpp
    src/Inflame.cpp
    src/BodySlam.cpp
    src/Entrench.cpp
    src/Relic.cpp
    src/Enemy.cpp
    src/TowerGuard.cpp
    src/Battle.cpp
)

# Tell the compiler where to find header files
target_include_directories(topple_logic PUBLIC include)
 
# Main executable
add_executable(topple_game src/main.cpp)
target_link_libraries(topple_game topple_logic)
 
# tests, one per topic. each registered with ctest
add_executable(test_counter tests/test_counter.cpp)
target_link_libraries(test_counter topple_logic)
add_test(NAME CounterTests COMMAND test_counter)

add_executable(test_character tests/test_character.cpp)
target_link_libraries(test_character topple_logic)
add_test(NAME CharacterTests COMMAND test_character)

add_executable(test_deck tests/test_deck.cpp)
target_link_libraries(test_deck topple_logic)
add_test(NAME DeckTests COMMAND test_deck)

add_executable(test_battle tests/test_battle.cpp)
target_link_libraries(test_battle topple_logic)
add_test(NAME BattleTests COMMAND test_battle)