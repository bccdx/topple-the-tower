# AI Prompts — Tower Map Feature

---

## Room and Map Structure

**Me:** implement the map class. a map has rooms. rooms can be battles, and other non implemented stuff like events, treasure, campfire, shop, etc.

**AI:** A good starting point is a `Room` base class with a `RoomType` enum, and subclasses for each type:

```cpp
enum RoomType { ROOM_BATTLE, ROOM_EVENT, ROOM_TREASURE, ROOM_CAMPFIRE, ROOM_SHOP };

class Room {
public:
    Room(RoomType type, const std::string& description);
    virtual ~Room() {}
    RoomType getType() const { return type_; }
    const std::string& getDescription() const { return description_; }
private:
    RoomType type_;
    std::string description_;
};
```

For battle rooms, subclass and add a `createEnemy()` method that returns a new enemy (caller owns the pointer). The non-battle room types can just be empty stubs for now — they'll compile and link, and you fill them in later.

A `TowerMap` class would own a `std::vector<Room*>` and be responsible for deleting them in its destructor.

**Me:** make blank (to be filled) subclasses for the other room types

**AI:** Here's the pattern — each one just passes its type up to the base constructor:

```cpp
class EventRoom : public Room {
public:
    EventRoom(const std::string& desc) : Room(ROOM_EVENT, desc) {}
};
```

Repeat for `TreasureRoom`, `CampfireRoom`, and `ShopRoom`. Since they have no new data members or behavior yet, the constructor is all you need.

---

## Enemy Difficulty Tiers

**Me:** for enemies, differentiate the difficulties into subfolders (basic, elite, boss) and track that in the class itself. make a few elites and bosses and add more basic enemies

**AI:** Add an `EnemyTier` enum to your base `Enemy` header and a protected `tier_` field:

```cpp
enum EnemyTier { TIER_BASIC, TIER_ELITE, TIER_BOSS };

class Enemy : public Character {
public:
    EnemyTier getTier() const { return tier_; }
protected:
    EnemyTier tier_;
};
```

Each subclass sets `tier_` in its constructor body. Then restructure your files into `enemies/basic/`, `enemies/elite/`, and `enemies/boss/` subdirectories and add all three to `target_include_directories` in CMakeLists so `#include "Slime.h"` still resolves without changing existing code.

**Me:** is TowerGuard actually a boss? classify him correctly, bosses should be the hardest

**AI:** No, 40 HP is definitely not boss level. In Slay the Spire terms, that's a mid-tier elite at best. A boss should have significantly more HP (140+) and a more threatening pattern. I'd move TowerGuard to the elite folder and set `tier_ = TIER_ELITE`. Reserve your boss slot for something like a 150 HP enemy with an escalating attack cycle.

**Me:** the stats for the enemies are really inconsistent compared to their difficulty. reference real slay the spire act 1 enemy stats to fix this. recategorize them too if needed

**AI:** Here are the STS Act 1 ranges to use as a guide:

- **Basic enemies** — 12 to 50 HP, 5 to 12 base damage. Examples: Red Louse (10–15 HP, bites for 5–7), Cultist (48 HP, gains 3 Strength per ritual then attacks for 6+), Jaw Worm (40–44 HP, Chomp 11 / Thrash 7+block / Bellow gain str+block).
- **Elite enemies** — 80 to 110 HP, 12 to 18 damage. Gremlin Nob (82 HP, enrages then attacks 14+), Lagavulin (109 HP, sleeps 2 turns, then Siphon Soul and heavy attacks).
- **Boss** — 140 to 250+ HP. Slime Boss ~140 HP, Hexaghost ~250 HP with multi-hit escalating attacks.

Bump your basic HP into the 16–50 range and make sure every elite sits above 75 HP. Damage should roughly scale 1.5x per tier.

**Me:** add some more bosses and some more other enemies

**AI:** Added CorruptKnight (150 HP, 4-turn escalating cycle: 16 / 16 / defend 12 / 22), Hexaghost (250 HP, Sear 6x2 / Inferno 8x3 / Activate +3 Strength), and SlimeBoss (140 HP, Slam 30 / Goop Weak+Frail). For basics added SpikeSlime (32 HP, Tackle 8 / Lick Frail). For elites added BruteGuard (80 HP, 14 / defend 10), StoneKnight (110 HP, 3-turn 9 / defend 12 / 16), and GoblinArcher (80 HP, arrow 10 / volley 6x2).

---

## Map Progression

**Me:** do randombasic randomelite randomboss simple 3 step map for now

**AI:** In your `TowerMap` constructor, define arrays of `EnemyKind` values for each tier and use `rand()` to pick one from each:

```cpp
BattleRoom::EnemyKind basics[] = { ENEMY_SLIME, ENEMY_LOUSE, ENEMY_CULTIST, ... };
int idx = rand() % 5;
rooms_.push_back(new BattleRoom(basics[idx], "Floor 1 -- something stirs in the dark"));
```

Repeat for elites and bosses. Make sure `srand` is seeded once in `main` before you construct the map, otherwise you'll get the same run every time.

---

## Ironknight Passive

**Me:** give ironknight his special ability of healing after combats, like the ironclad in slay the spire

**AI:** Add a virtual `onCombatEnd()` hook to your `Hero` base class with an empty default body, then override it in `Ironknight`:

```cpp
// Hero.h
virtual void onCombatEnd() {}

// Ironknight.cpp
void Ironknight::onCombatEnd() {
    heal(COMBAT_END_HEAL);
}
```

Call `hero.onCombatEnd()` in `main.cpp` right after the battle win check, before showing rewards. This keeps the passive logic in the hero class and the base `Hero` stays generic — future hero classes just override `onCombatEnd()` with their own ability.

---

## Terminal Layout Stability

**Me:** refresh the terminal on each print so it looks like a screen. keep newline placeholders for possible added lines so the position of the printed lines don't change on terminal refresh

**AI:** Two fixes:

1. **Fixed-width numbers** — use `std::setw()` from `<iomanip>` to right-align stats:
   ```cpp
   #include <iomanip>
   std::cout << "HP " << std::setw(3) << currentHp << "/" << maxHp;
   ```
   Use `setw(3)` for HP and block (handles up to 999), `setw(2)` for pile counts.

2. **Fixed-height hand** — always print a fixed number of card slots and pad with blank lines:
   ```cpp
   const int HAND_SLOTS = 10;
   for (int i = 0; i < HAND_SLOTS; i++) {
       if (i < (int)hand.size()) { /* print card info */ }
       else std::cout << "\n";
   }
   ```

With both changes the entire screen occupies the same number of lines every redraw, so the input prompt stays at the same row.

**Me:** clear the screen on win/loss/floor clear too so the results don't appear stuck to the last battle state

**AI:** Call `clearScreen()` (your `\033[2J\033[H` function) at the top of each of those branches before printing anything. The same function you already use for the in-battle refresh works fine here.
