#include "Hero.h"

Hero::Hero(const std::string& name, int maxHp, int maxEnergy) : Character(name, maxHp) {
    maxEnergy_ = maxEnergy;
    currentEnergy_ = maxEnergy;
    gold_ = 0;
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
}

void Hero::onTurnEnd() {
    deck_.discardHand();
    Character::onTurnEnd();           // tick down debuffs
}
