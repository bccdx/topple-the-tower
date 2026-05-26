#include "Enemy.h"

#include "Hero.h"

std::string intentTypeToString(IntentType t) {
    switch (t) {
        case INTENT_ATTACK:  return "Attack";
        case INTENT_DEFEND:  return "Defend";
        case INTENT_BUFF:    return "Buff";
        case INTENT_DEBUFF:  return "Debuff";
        case INTENT_UNKNOWN: return "Unknown";
    }
    return "?";
}

Enemy::Enemy(const std::string& name, int maxHp) : Character(name, maxHp) {
}

void Enemy::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_ATTACK) {
        for (int i = 0; i < intent_.hits; i++) {
            dealAttackDamage(target, intent_.value);
        }
    } else if (intent_.type == INTENT_DEFEND) {
        gainBlock(intent_.value);
    }
    // subclasses with richer behavior should override takeTurn
}
