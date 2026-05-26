# Topple The Tower
A roguelike deck building card game where the player climbs a tower and battles enemies to defeat the final boss.

## Features
- Terminal interface
- Turn-based battle system where the player plays cards from their hand using energy to attack, defend, and apply status effects to enemies
- A deck system with a draw pile, hand, discard pile, and exhaust pile that reshuffles when the draw pile is empty
- A map path for the player to travel / “climb the tower,” a single path to start
- Battle rewards / adding to deck: player chooses 0–1 cards from 3 randomly presented options to add to their deck
- At least one playable character class (the Ironknight) with a unique starter deck and card pool


## Current Status

**Implemented Features**:
- Single battle: Ironknight hero fights a Tower Guard enemy. Starter deck of 5 Strike + 4 Defend + 1 Bash. Full status system (Weak, Frail, Vulnerable, Strength, Dexterity, Artifact) wired into damage and Block math. Terminal UI shows enemy intent, hand, played cards this turn, and resolves win/lose.

**Planned (not yet implemented)**:
- Tower map / run structure (single path of fights)
- Battle rewards: choose 0–1 of 3 random card options after each fight
- Additional heroes beyond Ironknight
- Save / load
- Graphical UI

**Known Issues**:
- None known


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
