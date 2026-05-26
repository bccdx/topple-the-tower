#include "BruteGuard.h"

BruteGuard::BruteGuard() : Enemy("Brute Guard", STARTING_HP) {
    tier_ = TIER_ELITE;
    turnCounter_ = 0;
    chooseNextIntent();
}

void BruteGuard::chooseNextIntent() {
    if (turnCounter_ % 2 == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Heavy swing";
    } else {
        intent_.type = INTENT_DEFEND;
        intent_.value = DEFEND_BLOCK;
        intent_.hits = 1;
        intent_.description = "Shield up";
    }
    turnCounter_ += 1;
}
