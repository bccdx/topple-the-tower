# AI Prompts — Assassin Hero

---

## Assassin Class

**Me:** add assassin class that inherits hero, 70 hp 3 energy, starter deck 5 strikes 4 defends 1 neutralize, goes in include/characters/heroes and src/characters/heroes

**AI:** Created `Assassin` in `include/characters/heroes/` and `src/characters/heroes/`. 70 HP, 3 energy. Starter deck is 5 Strikes, 4 Defends, 1 Neutralize — same structure as Ironknight's constructor.

```cpp
Assassin::Assassin() : Hero("Assassin", STARTING_HP, STARTING_ENERGY) {
    for (int i = 0; i < NUM_STRIKES; i++)     deck_.addCard(new Strike());
    for (int i = 0; i < NUM_DEFENDS; i++)     deck_.addCard(new Defend());
    for (int i = 0; i < NUM_NEUTRALIZES; i++) deck_.addCard(new Neutralize());
    deck_.shuffleDrawPile();
}
```

---

## Ring of the Snake (Assassin Starter Relic)

**Me:** assassin's starting relic is ring of the snake, draws 2 extra at combat start. make ironclad's starting relic a relic too if it isn't already

**AI:** Added `RELIC_RING_OF_THE_SNAKE` to the `RelicType` enum. Both heroes now get their starter relic as an actual `Relic*` added in their constructors instead of hardcoded logic:

```cpp
// Assassin.cpp
addRelic(new Relic(RELIC_RING_OF_THE_SNAKE, "Ring of the Snake",
    "Draw 2 additional cards at the start of each combat"));

// Ironknight.cpp
addRelic(new Relic(RELIC_BURNING_BLOOD, "Burning Blood",
    "Heal 6 HP at the end of each combat"));
```

`Hero::onCombatStart` handles Ring of the Snake (draws 2), and `Hero::onCombatEnd` handles Burning Blood (heals 6). Removed the hardcoded `heal(COMBAT_END_HEAL)` call from `Ironknight::onCombatEnd`.

One tricky part: Burning Blood heals before Meat on the Bone checks, which could push HP above 50% and prevent the heal. Fixed by capturing eligibility before the loop:

```cpp
void Hero::onCombatEnd() {
    bool meatEligible = (currentHp_ * 2 <= maxHp_);
    for (int i = 0; i < (int)relics_.size(); i++) {
        switch (relics_[i]->getRelicType()) {
            case RELIC_BURNING_BLOOD:    heal(6); break;
            case RELIC_MEAT_ON_THE_BONE: if (meatEligible) heal(12); break;
            default: break;
        }
    }
}
```

---

## Dagger

**Me:** add a dagger attack card, 0 energy, deal 4 damage

**AI:** Created `Dagger` in `include/cards/assassin/` and `src/cards/assassin/`. 0-cost attack, deals 4 damage.

```cpp
Dagger::Dagger() : Card("Dagger", "Deal 4 damage.", 0, CARD_ATTACK, TARGET_ENEMY) {}

void Dagger::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
}
```

---

## Neutralize

**Me:** add neutralize attack card, 0 energy, 3 damage and apply 1 weak

**AI:** Created `Neutralize`. 0-cost attack. Damage resolves first, same order as Bash.

```cpp
Neutralize::Neutralize()
    : Card("Neutralize", "Deal 3 damage. Apply 1 Weak.", 0, CARD_ATTACK, TARGET_ENEMY) {}

void Neutralize::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_WEAK, WEAK_STACKS);
}
```

---

## Prepared

**Me:** add prepared skill card, 0 energy, draw 1 card

**AI:** Created `Prepared`. 0-cost skill.

```cpp
Prepared::Prepared()
    : Card("Prepared", "Draw 1 card.", 0, CARD_SKILL, TARGET_SELF) {}

void Prepared::play(Hero& source, Character& target, Battle& battle) {
    source.getDeck().draw(DRAW);
}
```

---

## Acrobatics

**Me:** add acrobatics skill card, 1 energy, draw 3

**AI:** Created `Acrobatics`. 1-cost skill.

```cpp
Acrobatics::Acrobatics()
    : Card("Acrobatics", "Draw 3 cards.", 1, CARD_SKILL, TARGET_SELF) {}

void Acrobatics::play(Hero& source, Character& target, Battle& battle) {
    source.getDeck().draw(DRAW);
}
```

---

## Dagger Spray

**Me:** add dagger spray attack card, 1 energy, deal 4 damage twice

**AI:** Created `DaggerSpray`. Same pattern as Twin Strike — loop `HITS` times.

```cpp
DaggerSpray::DaggerSpray()
    : Card("Dagger Spray", "Deal 4 damage twice.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void DaggerSpray::play(Hero& source, Character& target, Battle& battle) {
    for (int i = 0; i < HITS; i++) {
        source.dealAttackDamage(target, DAMAGE);
    }
}
```

---

## Dagger Throw

**Me:** add dagger throw attack card, 1 energy, 9 damage and draw 1

**AI:** Created `DaggerThrow`. Same pattern as Pommel Strike.

```cpp
DaggerThrow::DaggerThrow()
    : Card("Dagger Throw", "Deal 9 damage. Draw 1 card.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void DaggerThrow::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    source.getDeck().draw(DRAW);
}
```

---

## Dodge and Roll

**Me:** add dodge and roll skill card, 1 energy, 4 block and draw 1

**AI:** Created `DodgeAndRoll`. 1-cost skill.

```cpp
DodgeAndRoll::DodgeAndRoll()
    : Card("Dodge and Roll", "Gain 4 Block. Draw 1 card.", 1, CARD_SKILL, TARGET_SELF) {}

void DodgeAndRoll::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(BLOCK);
    source.getDeck().draw(DRAW);
}
```

---

## Backflip

**Me:** add backflip skill card, 1 energy, 5 block and draw 2

**AI:** Created `Backflip`. 1-cost skill.

```cpp
Backflip::Backflip()
    : Card("Backflip", "Gain 5 Block. Draw 2 cards.", 1, CARD_SKILL, TARGET_SELF) {}

void Backflip::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(BLOCK);
    source.getDeck().draw(DRAW);
}
```

---

## Footwork

**Me:** add footwork, 1 energy power, gives 2 dexterity

**AI:** Created `Footwork`. 1-cost power card.

```cpp
Footwork::Footwork()
    : Card("Footwork", "Gain 2 Dexterity.", 1, CARD_POWER, TARGET_SELF) {}

void Footwork::play(Hero& source, Character& target, Battle& battle) {
    source.applyStatus(STATUS_DEXTERITY, DEX);
}
```

---

## Poisoned Dagger

**Me:** add poisoned dagger attack card, 1 energy, 8 damage and 2 weak

**AI:** Created `PoisonedDagger`. Same pattern as Clothesline.

```cpp
PoisonedDagger::PoisonedDagger()
    : Card("Poisoned Dagger", "Deal 8 damage. Apply 2 Weak.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void PoisonedDagger::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_WEAK, WEAK_STACKS);
}
```

---

## Hero Selection Screen

**Me:** add a hero selection screen at the start of the game

**AI:** Added a `selectHero()` function that runs before the main game loop and returns a heap-allocated `Hero*`. The game loop now uses `Hero*` instead of a stack `Ironknight`, so both heroes work without duplicating any logic. Added `delete hero` at each exit point (defeat, win, stdin closed).

```cpp
static Hero* selectHero() {
    clearScreen();
    std::cout << "Choose your hero:\n\n";
    std::cout << "  1) Ironknight  80 HP  |  armored warrior, heals after every fight\n";
    std::cout << "  2) Assassin    70 HP  |  quick and precise, draws 2 extra cards each combat\n\n";

    std::string input;
    while (true) {
        std::cout << "Enter 1 or 2 > ";
        if (!std::getline(std::cin, input)) return NULL;
        if (input == "1") return new Ironknight();
        if (input == "2") return new Assassin();
        std::cout << "Enter 1 or 2.\n";
    }
}
```

`Reward::generateOptions` was updated to take a `const Hero&` so card rewards pull from the right pool per hero — Assassin gets Assassin cards, Ironknight gets Ironknight cards.
