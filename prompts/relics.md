# AI Prompts — Relic Passives Feature

---

## Relic Type System

**Me:** relics currently just store a name and description. how do i give them actual effects

**AI:** The cleanest approach is to add a `RelicType` enum so each relic instance knows what it is, then check the type at each trigger point:

```cpp
enum RelicType {
    RELIC_BURNING_BLOOD,
    RELIC_VAJRA,
    RELIC_ANCHOR,
    // ...
};

class Relic {
public:
    Relic(RelicType type, const std::string& name, const std::string& description);
    RelicType getRelicType() const { return type_; }
private:
    RelicType type_;
    // ...
};
```

Update `Reward::awardRelic` to pass the right type when constructing each relic. Then hero methods can loop through `relics_` and switch on the type.

---

## Combat Start Effects

**Me:** some relics trigger at the start of combat (vajra, anchor, bag of marbles, etc). where do i put that

**AI:** Add an `onCombatStart(Enemy& enemy)` hook to `Hero` and call it from `Battle::start()`. You need the enemy reference for Bag of Marbles (applies Vulnerable). Call it after `startHeroTurn()` so Anchor's block doesn't get wiped by the block clear in `onTurnStart`:

```cpp
void Battle::start() {
    turnNumber_ = 1;
    startHeroTurn();
    hero_.onCombatStart(*enemy_);
}

void Hero::onCombatStart(Enemy& enemy) {
    for (int i = 0; i < (int)relics_.size(); i++) {
        switch (relics_[i]->getRelicType()) {
            case RELIC_ANCHOR:
                gainBlock(10); break;
            case RELIC_VAJRA:
                applyStatus(STATUS_STRENGTH, 1); break;
            case RELIC_BAG_OF_MARBLES:
                enemy.applyStatus(STATUS_VULNERABLE, 1); break;
            // ...
        }
    }
}
```

---

## Damage-Triggered Effects

**Me:** paper krane reduces incoming damage by 1, centennial puzzle draws 3 cards the first time you lose hp. how do those work

**AI:** Make `takeDamage` virtual in `Character` and override it in `Hero`. Paper Krane reduces the amount before passing to the base, Centennial Puzzle checks if HP actually went down after the hit:

```cpp
void Hero::takeDamage(int amount) {
    for (int i = 0; i < (int)relics_.size(); i++) {
        if (relics_[i]->getRelicType() == RELIC_PAPER_KRANE) amount -= 1;
    }
    if (amount <= 0) return;
    int hpBefore = currentHp_;
    Character::takeDamage(amount);
    bool hpLost = currentHp_ < hpBefore;
    if (hpLost && !puzzleTriggered_) {
        for (int i = 0; i < (int)relics_.size(); i++) {
            if (relics_[i]->getRelicType() == RELIC_CENTENNIAL_PUZZLE) {
                deck_.draw(3);
                puzzleTriggered_ = true;
                break;
            }
        }
    }
}
```

Add a `bool puzzleTriggered_` flag to `Hero` and reset it in `onCombatStart`.

**Me:** bronze scales deals 3 damage back when you take damage. that also needs the enemy reference which takeDamage doesn't have

**AI:** Track hero HP before the enemy acts and retaliate in `Battle::runEnemyTurn` after the enemy's turn resolves:

```cpp
void Battle::runEnemyTurn() {
    int heroBefore = hero_.getCurrentHp();
    enemy_->onTurnStart();
    enemy_->takeTurn(hero_, *this);
    int hpLost = heroBefore - hero_.getCurrentHp();
    refreshState();
    if (state_ != BATTLE_ONGOING) return;
    if (hpLost > 0) {
        int retaliation = hero_.getBronzeScalesDamage();
        if (retaliation > 0) {
            enemy_->takeDamage(retaliation);
            refreshState();
        }
    }
    // ...
}
```

Add `getBronzeScalesDamage()` to `Hero` — returns 3 per Bronze Scales relic.

---

## Red Skull

**Me:** red skull gives 3 strength while at or below 50% hp. it should go away when you heal above 50%

**AI:** Track it with a `redSkullActive_` flag and check in `Hero::onTurnStart` each turn:

```cpp
void Hero::onTurnStart() {
    Character::onTurnStart();
    currentEnergy_ = maxEnergy_;
    deck_.draw(DEFAULT_DRAW);

    bool belowHalf = (currentHp_ * 2 <= maxHp_);
    if (hasRedSkull) {
        if (belowHalf && !redSkullActive_) {
            applyStatus(STATUS_STRENGTH, 3);
            redSkullActive_ = true;
        } else if (!belowHalf && redSkullActive_) {
            statuses_[STATUS_STRENGTH] -= 3;
            if (statuses_[STATUS_STRENGTH] < 0) statuses_[STATUS_STRENGTH] = 0;
            redSkullActive_ = false;
        }
    }
}
```

Reset `redSkullActive_` to false in `onCombatStart` so it re-evaluates each combat.

---

## End of Combat Effects

**Me:** meat on the bone heals 12 if you're at or below 50% hp at the end of combat. ironknight already has an onCombatEnd. how do i add relic effects without breaking his passive

**AI:** Put relic end-of-combat logic in a base `Hero::onCombatEnd()` implementation, and have Ironknight call it first before his own heal:

```cpp
// Hero.cpp
void Hero::onCombatEnd() {
    for (int i = 0; i < (int)relics_.size(); i++) {
        if (relics_[i]->getRelicType() == RELIC_MEAT_ON_THE_BONE) {
            if (currentHp_ * 2 <= maxHp_) heal(12);
        }
    }
}

// Ironknight.cpp
void Ironknight::onCombatEnd() {
    Hero::onCombatEnd();    // relic effects first
    heal(COMBAT_END_HEAL);
}
```
