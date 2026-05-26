#include "Cultist.h"

Cultist::Cultist() : Enemy("Cultist", STARTING_HP) {
    tier_ = TIER_BASIC;
    turnCounter_ = 0;
    chooseNextIntent();
}

void Cultist::chooseNextIntent() {
    if (turnCounter_ % 2 == 0) {
        intent_.type = INTENT_BUFF;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Incantation";
    } else {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Dark Strike";
    }
    turnCounter_ += 1;
}

void Cultist::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_BUFF) {
        applyStatus(STATUS_STRENGTH, RITUAL_STRENGTH);
    } else {
        Enemy::takeTurn(target, battle);
    }
}
