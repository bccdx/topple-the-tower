#include "Slime.h"

Slime::Slime() : Enemy("Slime", STARTING_HP) {
    tier_ = TIER_BASIC;
    chooseNextIntent();
}

void Slime::chooseNextIntent() {
    intent_.type = INTENT_ATTACK;
    intent_.value = ATTACK_DAMAGE;
    intent_.hits = 1;
    intent_.description = "Lunge";
}
