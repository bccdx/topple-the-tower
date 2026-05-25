#include "Character.h"

Character::Character(const std::string& name, int maxHp) {
    name_ = name;
    maxHp_ = maxHp;
    currentHp_ = maxHp;
}

void Character::takeDamage(int amount) {
    if (amount <= 0) return;
    currentHp_ -= amount;
    if (currentHp_ < 0) currentHp_ = 0;
}

void Character::heal(int amount) {
    if (amount <= 0) return;
    currentHp_ += amount;
    if (currentHp_ > maxHp_) currentHp_ = maxHp_;
}
