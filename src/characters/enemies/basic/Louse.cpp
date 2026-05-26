#include "Louse.h"

Louse::Louse() : Enemy("Louse", STARTING_HP) {
    tier_ = TIER_BASIC;
    chooseNextIntent();
}

void Louse::chooseNextIntent() {
    intent_.type = INTENT_ATTACK;
    intent_.value = ATTACK_DAMAGE;
    intent_.hits = 1;
    intent_.description = "Bite";
}
