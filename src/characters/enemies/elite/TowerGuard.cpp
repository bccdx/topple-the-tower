#include "TowerGuard.h"

TowerGuard::TowerGuard() : Enemy("Tower Guard", STARTING_HP) {
    tier_ = TIER_ELITE;
    turnCounter_ = 0;
    chooseNextIntent();
}

void TowerGuard::chooseNextIntent() {
    if (turnCounter_ % 2 == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Heavy slash";
    } else {
        intent_.type = INTENT_DEFEND;
        intent_.value = DEFEND_BLOCK;
        intent_.hits = 1;
        intent_.description = "Raises shield";
    }
    turnCounter_ += 1;
}
