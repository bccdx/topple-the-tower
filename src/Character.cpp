#include "Character.h"

Character::Character(const std::string& name, int maxHp) {
    name_ = name;
    maxHp_ = maxHp;
    currentHp_ = maxHp;
    block_ = 0;
}

void Character::takeDamage(int amount) {
    if (amount <= 0) return;
    if (block_ >= amount) {
        block_ -= amount;
        return;
    }
    int leftover = amount - block_;
    block_ = 0;
    currentHp_ -= leftover;
    if (currentHp_ < 0) currentHp_ = 0;
}

void Character::gainBlock(int amount) {
    if (amount <= 0) return;
    block_ += amount;
}

void Character::heal(int amount) {
    if (amount <= 0) return;
    currentHp_ += amount;
    if (currentHp_ > maxHp_) currentHp_ = maxHp_;
}

int Character::dealAttackDamage(Character& target, int baseDamage) {
    int dmg = baseDamage;
    if (dmg < 0) dmg = 0;
    int hpBefore = target.getCurrentHp();
    target.takeDamage(dmg);
    return hpBefore - target.getCurrentHp();
}

void Character::onTurnStart() {
    block_ = 0;
}

void Character::onTurnEnd() {
    // no-op for now
}
