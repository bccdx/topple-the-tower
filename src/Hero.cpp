#include "Hero.h"

Hero::Hero(const std::string& name, int maxHp, int maxEnergy) : Character(name, maxHp) {
    maxEnergy_ = maxEnergy;
    currentEnergy_ = maxEnergy;
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
}
