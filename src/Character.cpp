#include "Character.h"

std::string statusToString(StatusType s) {
    switch (s) {
        case STATUS_WEAK:       return "Weak";
        case STATUS_FRAIL:      return "Frail";
        case STATUS_VULNERABLE: return "Vulnerable";
        case STATUS_STRENGTH:   return "Strength";
        case STATUS_DEXTERITY:  return "Dexterity";
        case STATUS_ARTIFACT:   return "Artifact";
        default: return "?";
    }
}

bool isDebuff(StatusType s) {
    if (s == STATUS_WEAK) return true;
    if (s == STATUS_FRAIL) return true;
    if (s == STATUS_VULNERABLE) return true;
    return false;
}

bool ticksDownEachTurn(StatusType s) {
    return isDebuff(s);
}

Character::Character(const std::string& name, int maxHp) {
    name_ = name;
    maxHp_ = maxHp;
    currentHp_ = maxHp;
    block_ = 0;
    for (int i = 0; i < STATUS_COUNT; i++) {
        statuses_[i] = 0;
    }
}

int Character::getStatus(StatusType s) const {
    return statuses_[s];
}

void Character::applyStatus(StatusType s, int amount) {
    if (amount <= 0) return;
    // one Artifact eats one whole debuff application no matter the stack size
    if (isDebuff(s) && statuses_[STATUS_ARTIFACT] > 0) {
        statuses_[STATUS_ARTIFACT] -= 1;
        return;
    }
    statuses_[s] += amount;
}

void Character::removeStatus(StatusType s) {
    statuses_[s] = 0;
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

void Character::takeHpLoss(int amount) {
    if (amount <= 0) return;
    currentHp_ -= amount;
    if (currentHp_ < 0) currentHp_ = 0;
}

void Character::gainBlock(int amount) {
    if (amount <= 0) return;
    int total = amount + statuses_[STATUS_DEXTERITY];
    if (statuses_[STATUS_FRAIL] > 0) {
        total = total * 3 / 4;   // 25% less Block while Frail
    }
    if (total < 0) total = 0;
    block_ += total;
}

void Character::heal(int amount) {
    if (amount <= 0) return;
    currentHp_ += amount;
    if (currentHp_ > maxHp_) currentHp_ = maxHp_;
}

int Character::dealAttackDamage(Character& target, int baseDamage) {
    int dmg = baseDamage + statuses_[STATUS_STRENGTH];
    if (statuses_[STATUS_WEAK] > 0)              dmg = dmg * 3 / 4;
    if (target.getStatus(STATUS_VULNERABLE) > 0) dmg = dmg * 3 / 2;
    if (dmg < 0) dmg = 0;
    int hpBefore = target.getCurrentHp();
    target.takeDamage(dmg);
    return hpBefore - target.getCurrentHp();   // HP actually lost (post-Block)
}

void Character::onTurnStart() {
    block_ = 0;
}

void Character::onTurnEnd() {
    for (int i = 0; i < STATUS_COUNT; i++) {
        StatusType s = (StatusType)i;
        if (ticksDownEachTurn(s) && statuses_[i] > 0) {
            statuses_[i] -= 1;
        }
    }
}
