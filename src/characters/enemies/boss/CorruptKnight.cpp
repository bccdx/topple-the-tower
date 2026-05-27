#include "CorruptKnight.h"

CorruptKnight::CorruptKnight() : Enemy("Corrupt Knight", STARTING_HP) {
    tier_ = TIER_BOSS;
    turnCounter_ = 0;
    chooseNextIntent();
}

void CorruptKnight::chooseNextIntent() {
    int phase = turnCounter_ % 4;
    if (phase == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_A;
        intent_.hits = 1;
        intent_.description = "Dark slash";
    } else if (phase == 1) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_B;
        intent_.hits = 1;
        intent_.description = "Dark slash";
    } else if (phase == 2) {
        intent_.type = INTENT_DEFEND;
        intent_.value = DEFEND_BLOCK;
        intent_.hits = 1;
        intent_.description = "Corrupted shield";
    } else {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_C;
        intent_.hits = 1;
        intent_.description = "Ruin";
    }
    turnCounter_ += 1;
}
