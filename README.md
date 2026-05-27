# Topple The Tower
A roguelike deck building card game where the player climbs a tower and battles enemies to defeat the final boss.

## Features
- Terminal interface with ASCII battle sprites and per-card animations
- Turn-based battle system where the player plays cards from their hand using energy to attack, defend, and apply status effects to enemies
- A deck system with a draw pile, hand, discard pile, and exhaust pile that reshuffles when the draw pile is empty
- Tower map: a single path of 3 rooms (basic enemy, elite, boss) with randomized enemy selection per tier
- Battle rewards: after winning, the hero earns gold, a random relic from a pool of 10, and can pick one of 3 cards to add to their deck (AI-assisted, see [docs/ai_collaboration.md](docs/ai_collaboration.md))
- Two playable hero classes with unique starter decks, card pools, and starting relics
- 10 relics with real passive effects (Burning Blood, Anchor, Vajra, Red Skull, Bronze Scales, and more)


## Current Status

**Implemented**:
- Full battle system: status effects (Weak, Frail, Vulnerable, Strength, Dexterity, Artifact) wired into damage and block math, enemy intents, win/lose resolution
- Tower map: 3-room run with randomized basic, elite, and boss enemies across 5 basics, 6 elites, and 3 bosses
- Ironknight: 80 HP warrior, starter deck of 5 Strike + 4 Defend + 1 Bash, 10-card reward pool, starting relic Burning Blood (heal 6 HP after each combat)
- Assassin: 70 HP agile hero, starter deck of 5 Strike + 4 Defend + 1 Neutralize, 10-card reward pool, starting relic Ring of the Snake (draw 2 extra cards at combat start)
- Hero selection screen at game start
- 10 relics with active effects: Burning Blood, Anchor, Vajra, Bag of Marbles, Oddly Smooth Stone, Red Skull, Bronze Scales, Centennial Puzzle, Paper Krane, Meat on the Bone
- ASCII battle sprites for both heroes and all enemy tiers, with attack/skill/power animations

**Planned (not yet implemented)**:
- Full map with branching paths, random graph structure, and gameplay-balanced room distribution (currently a fixed 3-room linear path)
- Multiple acts with distinct enemy sets, elites, bosses, and escalating difficulty
- More hero classes
- Non-battle rooms (events, treasure, campfire, shop)
- Card upgrades (at campfire or shop)
- Card removal (at shop or events)
- Boss relics awarded after each act boss
- Additional status effects (Poison, Burn, Stun)
- Curse cards
- Ascension mode (progressive difficulty modifiers that unlock after each win)
- Save / load
- Graphical UI

**Known Issues**:
- Card descriptions always show base damage values and don't reflect active Strength, Weak, or Vulnerable modifiers (damage math resolves correctly, the text is just static)


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
