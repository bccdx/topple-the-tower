# Battle Rewards — Spec

## Problem statement

After winning a fight the hero gets gold and a random relic automatically, then gets
to pick one of 3 cards to add to their deck (or skip the card)

Before this feature the game just printed "Victory!" and ended

## Types involved

- `Reward` (new): holds the card options and gold, gives out relics
- `Relic` (new): just a name and description for now, no effects yet
- `Hero`: needs gold and relic fields added
- `Deck`: already has `addCard()`, nothing to change
- `main.cpp`: show the reward screen after `BATTLE_HERO_WON`

## Public interface

```cpp
class Relic {
public:
    Relic(const std::string& name, const std::string& description);
    const std::string& getName() const;
    const std::string& getDescription() const;
};

class Reward {
public:
    Reward();
    ~Reward();

    void setGold(int amount);
    void awardRelic(Hero& hero);       // picks a random relic and gives it to the hero
    void generateOptions(int n);       // fill with n random cards from the pool
    bool pickCard(int index, Hero& hero); // returns false if index is out of range

    int getGold() const;
    const std::vector<Card*>& getOptions() const;
    int optionCount() const;

private:
    std::vector<Card*> options_;
    int gold_;
};

// additions to Hero
void Hero::earnGold(int amount);
int  Hero::getGold() const;
void Hero::addRelic(Relic* relic);
const std::vector<Relic*>& Hero::getRelics() const;
```

## Inputs and outputs

- gold prints automatically: `"You earned 25 gold. (Total: 25)"`
- relic prints automatically: `"You found <RelicName>: <description>"`
- card pick: player types `1`-`3`, prints `"Added <CardName> to your deck."`
- skip: player types `0`, prints `"Skipped."`
- anything else re-prompts

## Edge cases

1. player skips card pick — deck stays the same (gold and relic already given)
2. player enters a number out of range — re-prompt, no crash
3. `generateOptions(n)` when pool has fewer than `n` cards — just use all of them
4. `generateOptions(0)` — no options, `pickCard` always returns false
5. picking index 0 and index `optionCount - 1` both work (no off-by-one)

## Three tests (English version)

- normal: generate 3 options, pick index 1, hero's draw pile grows by 1
- edge: `pickCard(99, hero)` returns false, deck unchanged
- boundary: pick index 0 works, pick index `optionCount - 1` works

## Card pool (10 non-basic cards)

| Card | Cost | Effect |
|---|---|---|
| Iron Wave | 1 | deal 5 damage + gain 5 block |
| Cleave | 1 | deal 8 damage |
| Pommel Strike | 1 | deal 9 damage + draw 1 card |
| Shrug It Off | 1 | gain 8 block + draw 1 card |
| Clothesline | 2 | deal 12 damage + apply 1 Weak |
| Twin Strike | 1 | deal 5 damage twice |
| Thunderclap | 1 | deal 4 damage + apply 1 Vulnerable |
| Inflame | 1 | gain 2 Strength |
| Body Slam | 1 | deal damage equal to current block |
| Entrench | 2 | gain block equal to current block |

## Relic pool (10 relics)

| Relic | Effect (stubbed) |
|---|---|
| Burning Blood | at the start of combat, heal 6 HP |
| Vajra | gain 1 Strength at the start of each combat |
| Anchor | start each combat with 10 Block |
| Bronze Scales | whenever you take damage, deal 3 back |
| Bag of Marbles | at the start of combat, apply 1 Vulnerable to all enemies |
| Centennial Puzzle | first time you lose HP each combat, draw 3 cards |
| Red Skull | while HP is at or below 50%, gain 3 Strength |
| Meat on the Bone | if HP is at or below 50% at end of combat, heal 12 HP |
| Oddly Smooth Stone | at the start of each combat, gain 1 Dexterity |
| Paper Krane | reduce all incoming attack damage by 1 |

## Design decisions

`Reward` owns the card options as pointers. Gold is just an int. Relics go straight
to the hero in `awardRelic()` so Reward doesn't need to hold one.

`pickCard()` moves one card pointer into the hero's deck and sets that slot to `NULL`
so the destructor doesn't delete it twice.

Relic effects are stubbed. The class just holds a name and description until a later
feature adds the actual passive hooks.

Gold doesn't do anything yet but it's tracked on Hero so adding a shop later is easier.
