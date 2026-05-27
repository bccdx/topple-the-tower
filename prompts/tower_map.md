# AI Prompts — Tower Map Feature

---

## Room and Map Structure

**Me:** I'm building a roguelike card game in C++ and want to add a map. The map has a path of rooms. Rooms can be battles but I also want to add events, treasure, campfires, and shops later. How  I design this?

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

**Me:** make stub subclasses for the other room types

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

**Me:** I want to organize enemies by difficulty tier — basic, elite, boss — in subfolders, and track the tier in the class itself. How would you approach this?

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

**Me:** is TowerGuard a boss? he has 40 HP and alternates attack 12 / defend 8

**AI:** No, 40 HP is definitely not boss level. In Slay the Spire terms, that's a mid-tier elite at best. A boss should have significantly more HP (140+) and a more threatening pattern. I'd move TowerGuard to the elite folder and set `tier_ = TIER_ELITE`. Reserve your boss slot for something like a 150 HP enemy with an escalating attack cycle.

**Me:** the enemy stats feel inconsistent — basic enemies have low HP but fairly high damage, and some elites have less HP than the basics. can you reference slay the spire act 1 enemy stats to fix this

**AI:** Here are the STS Act 1 ranges to use as a guide:

- **Basic enemies** — 12 to 50 HP, 5 to 12 base damage. Examples: Red Louse (10–15 HP, bites for 5–7), Cultist (48 HP, gains 3 Strength per ritual then attacks for 6+), Jaw Worm (40–44 HP, Chomp 11 / Thrash 7+block / Bellow gain str+block).
- **Elite enemies** — 80 to 110 HP, 12 to 18 damage. Gremlin Nob (82 HP, enrages then attacks 14+), Lagavulin (109 HP, sleeps 2 turns, then Siphon Soul and heavy attacks).
- **Boss** — 140 to 250+ HP. Slime Boss ~140 HP, Hexaghost ~250 HP with multi-hit escalating attacks.

Bump your basic HP into the 16–50 range and make sure every elite sits above 75 HP. Damage should roughly scale 1.5x per tier.

---

## Map Progression

**Me:** I have 5 floors with fixed enemies right now. I want to make it so the map randomly picks one enemy from the basic pool, one from the elite pool, and one from the boss pool each run. 3 floors total for now.

**AI:** In your `TowerMap` constructor, define arrays of `EnemyKind` values for each tier and use `rand()` to pick one from each:

```cpp
BattleRoom::EnemyKind basics[] = { ENEMY_SLIME, ENEMY_LOUSE, ENEMY_CULTIST, ... };
int idx = rand() % 5;
rooms_.push_back(new BattleRoom(basics[idx], "Floor 1 -- something stirs in the dark"));
```

Repeat for elites and bosses. Make sure `srand` is seeded once in `main` before you construct the map, otherwise you'll get the same run every time.

---

## Ironknight Passive

**Me:** I want the Ironknight to heal 6 HP after each combat like the Ironclad's Burning Blood in slay the spire. where's the right place to put this?

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

**Me:** The battle screen flickers and shifts when it refreshes — HP going from two digits to one digit moves the block label, and the hand changes height each turn so the input prompt jumps around. How do I fix this?

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

**Me:** also clear the screen on win/loss/floor clear so the results don't appear stuck to the last battle state

**AI:** Call `clearScreen()` (your `\033[2J\033[H` function) at the top of each of those branches before printing anything. The same function you already use for the in-battle refresh works fine here.