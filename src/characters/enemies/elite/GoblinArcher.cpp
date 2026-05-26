#include "GoblinArcher.h"

GoblinArcher::GoblinArcher() : Enemy("Goblin Archer", STARTING_HP) {
    tier_ = TIER_ELITE;
    turnCounter_ = 0;
    chooseNextIntent();
}

void GoblinArcher::chooseNextIntent() {
    if (turnCounter_ % 2 == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ARROW_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Arrow";
    } else {
        intent_.type = INTENT_ATTACK;
        intent_.value = VOLLEY_DAMAGE;
        intent_.hits = 2;
        intent_.description = "Volley";
    }
    turnCounter_ += 1;
}
