cmake_minimum_required(VERSION 3.10)
project(ToppleTheTower)

set(CMAKE_CXX_STANDARD 11)

# Enable testing
enable_testing()

# game logic. linked by both the game and the tests
add_library(topple_logic
    src/Counter.cpp
    src/cards/Card.cpp
    src/Deck.cpp
    src/characters/Character.cpp
    src/characters/heroes/Hero.cpp
    src/characters/heroes/Ironknight.cpp
    src/cards/basic/Strike.cpp
    src/cards/basic/Defend.cpp
    src/cards/ironknight/Bash.cpp
    src/cards/ironknight/IronWave.cpp
    src/cards/ironknight/Cleave.cpp
    src/cards/ironknight/PommelStrike.cpp
    src/cards/ironknight/ShrugItOff.cpp
    src/cards/ironknight/Clothesline.cpp
    src/cards/ironknight/TwinStrike.cpp
    src/cards/ironknight/Thunderclap.cpp
    src/cards/ironknight/Inflame.cpp
    src/cards/ironknight/BodySlam.cpp
    src/cards/ironknight/Entrench.cpp
    src/Relic.cpp
    src/Reward.cpp
    src/characters/enemies/Enemy.cpp
    src/characters/enemies/TowerGuard.cpp
    src/Battle.cpp
)

# Tell the compiler where to find header files
target_include_directories(topple_logic PUBLIC
    include
    include/cards
    include/cards/basic
    include/cards/colorless
    include/cards/ironknight
    include/characters
    include/characters/heroes
    include/characters/enemies
)

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

add_executable(test_reward tests/test_reward.cpp)
target_link_libraries(test_reward topple_logic)
add_test(NAME RewardTests COMMAND test_reward)
