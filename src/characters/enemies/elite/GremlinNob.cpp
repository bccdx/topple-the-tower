#include "GremlinNob.h"

GremlinNob::GremlinNob() : Enemy("Gremlin Nob", STARTING_HP) {
    tier_ = TIER_ELITE;
    turnCounter_ = 0;
    chooseNextIntent();
}

void GremlinNob::chooseNextIntent() {
    if (turnCounter_ == 0) {
        intent_.type = INTENT_BUFF;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Enrage";
    } else {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Skull Bash";
    }
    turnCounter_ += 1;
}

void GremlinNob::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_BUFF) {
        applyStatus(STATUS_STRENGTH, ENRAGE_STR);
    } else {
        Enemy::takeTurn(target, battle);
    }
}
