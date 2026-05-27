#include "StoneKnight.h"

StoneKnight::StoneKnight() : Enemy("Stone Knight", STARTING_HP) {
    tier_ = TIER_ELITE;
    turnCounter_ = 0;
    chooseNextIntent();
}

void StoneKnight::chooseNextIntent() {
    int phase = turnCounter_ % 3;
    if (phase == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Slash";
    } else if (phase == 1) {
        intent_.type = INTENT_DEFEND;
        intent_.value = DEFEND_BLOCK;
        intent_.hits = 1;
        intent_.description = "Brace";
    } else {
        intent_.type = INTENT_ATTACK;
        intent_.value = HEAVY_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Crushing blow";
    }
    turnCounter_ += 1;
}
