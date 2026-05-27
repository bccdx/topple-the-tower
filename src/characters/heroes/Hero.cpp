#include "Hero.h"
#include "Enemy.h"

Hero::Hero(const std::string& name, int maxHp, int maxEnergy) : Character(name, maxHp) {
    maxEnergy_ = maxEnergy;
    currentEnergy_ = maxEnergy;
    gold_ = 0;
    puzzleTriggered_ = false;
    redSkullActive_ = false;
}

Hero::~Hero() {
    for (int i = 0; i < (int)relics_.size(); i++) {
        delete relics_[i];
    }
}

void Hero::earnGold(int amount) {
    if (amount > 0) gold_ += amount;
}

void Hero::addRelic(Relic* relic) {
    relics_.push_back(relic);
}

void Hero::spendEnergy(int amount) {
    currentEnergy_ -= amount;
    if (currentEnergy_ < 0) currentEnergy_ = 0;
}

void Hero::gainEnergy(int amount) {
    currentEnergy_ += amount;
}

void Hero::onTurnStart() {
    Character::onTurnStart();         // clear Block
    currentEnergy_ = maxEnergy_;
    deck_.draw(DEFAULT_DRAW);

    // Red Skull: +3 Strength while at or below 50% HP, removed when above
    bool hasRedSkull = false;
    for (int i = 0; i < (int)relics_.size(); i++) {
        if (relics_[i]->getRelicType() == RELIC_RED_SKULL) {
            hasRedSkull = true;
            break;
        }
    }
    if (hasRedSkull) {
        bool belowHalf = (currentHp_ * 2 <= maxHp_);
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

void Hero::onTurnEnd() {
    deck_.discardHand();
    Character::onTurnEnd();           // tick down debuffs
}

void Hero::onCombatStart(Enemy& enemy) {
    puzzleTriggered_ = false;
    for (int i = 0; i < (int)relics_.size(); i++) {
        switch (relics_[i]->getRelicType()) {
            case RELIC_VAJRA:
                applyStatus(STATUS_STRENGTH, 1);
                break;
            case RELIC_ANCHOR:
                gainBlock(10);
                break;
            case RELIC_BAG_OF_MARBLES:
                enemy.applyStatus(STATUS_VULNERABLE, 1);
                break;
            case RELIC_ODDLY_SMOOTH_STONE:
                applyStatus(STATUS_DEXTERITY, 1);
                break;
            case RELIC_RING_OF_THE_SNAKE:
                deck_.draw(2);
                break;
            default:
                break;
        }
    }
}

void Hero::onCombatEnd() {
    // check eligibility before any healing so Burning Blood doesn't disqualify Meat on the Bone
    bool meatEligible = (currentHp_ * 2 <= maxHp_);
    for (int i = 0; i < (int)relics_.size(); i++) {
        switch (relics_[i]->getRelicType()) {
            case RELIC_BURNING_BLOOD:
                heal(6);
                break;
            case RELIC_MEAT_ON_THE_BONE:
                if (meatEligible) heal(12);
                break;
            default:
                break;
        }
    }
}

void Hero::takeDamage(int amount) {
    // Paper Krane: reduce incoming damage by 1
    for (int i = 0; i < (int)relics_.size(); i++) {
        if (relics_[i]->getRelicType() == RELIC_PAPER_KRANE) {
            amount -= 1;
        }
    }
    if (amount <= 0) return;

    int hpBefore = currentHp_;
    Character::takeDamage(amount);
    bool hpLost = currentHp_ < hpBefore;

    // Centennial Puzzle: first time HP is lost this combat, draw 3
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

int Hero::getBronzeScalesDamage() const {
    int total = 0;
    for (int i = 0; i < (int)relics_.size(); i++) {
        if (relics_[i]->getRelicType() == RELIC_BRONZE_SCALES) {
            total += 3;
        }
    }
    return total;
}
