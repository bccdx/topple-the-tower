#include "Hexaghost.h"

Hexaghost::Hexaghost() : Enemy("Hexaghost", STARTING_HP) {
    tier_ = TIER_BOSS;
    turnCounter_ = 0;
    chooseNextIntent();
}

void Hexaghost::chooseNextIntent() {
    int phase = turnCounter_ % 3;
    if (phase == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = SEAR_DAMAGE;
        intent_.hits = 2;
        intent_.description = "Sear";
    } else if (phase == 1) {
        intent_.type = INTENT_ATTACK;
        intent_.value = INFERNO_DAMAGE;
        intent_.hits = 3;
        intent_.description = "Inferno";
    } else {
        intent_.type = INTENT_BUFF;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Activate";
    }
    turnCounter_ += 1;
}

void Hexaghost::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_BUFF) {
        applyStatus(STATUS_STRENGTH, ACTIVATE_STR);
    } else {
        Enemy::takeTurn(target, battle);
    }
}
