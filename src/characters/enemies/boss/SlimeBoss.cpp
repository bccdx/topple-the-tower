#include "SlimeBoss.h"
#include "Hero.h"

SlimeBoss::SlimeBoss() : Enemy("Slime Boss", STARTING_HP) {
    tier_ = TIER_BOSS;
    turnCounter_ = 0;
    chooseNextIntent();
}

void SlimeBoss::chooseNextIntent() {
    if (turnCounter_ % 2 == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = SLAM_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Slam";
    } else {
        intent_.type = INTENT_DEBUFF;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Goop";
    }
    turnCounter_ += 1;
}

void SlimeBoss::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_DEBUFF) {
        target.applyStatus(STATUS_WEAK,  GOOP_WEAK);
        target.applyStatus(STATUS_FRAIL, GOOP_FRAIL);
    } else {
        Enemy::takeTurn(target, battle);
    }
}
