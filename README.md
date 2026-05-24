# Topple The Tower
A roguelike deck building card game where the player climbs a tower and battles enemies to defeat the final boss.

## Features
- Terminal interface
- Turn-based battle system where the player plays cards from their hand using energy to attack, defend, and apply status effects to enemies
- A deck system with a draw pile, hand, discard pile, and exhaust pile that reshuffles when the draw pile is empty
- A map path for the player to travel / “climb the tower,” a single path to start
- Battle rewards / adding to deck: player chooses 0–1 cards from 3 randomly presented options to add to their deck
- At least one playable character class (Ironclad?) with a unique starter deck and card pool


## Building
```
cmake -S . -B build
cmake --build build
```

## Running
```
./build/topple_game
```

## Running Tests
```
ctest --test-dir build --verbose
```

## Author
Danna Xu - CIS 25 Final Project
