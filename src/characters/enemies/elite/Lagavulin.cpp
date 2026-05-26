#include "Lagavulin.h"
#include "Hero.h"

Lagavulin::Lagavulin() : Enemy("Lagavulin", STARTING_HP) {
    tier_ = TIER_ELITE;
    turnCounter_ = 0;
    chooseNextIntent();
}

void Lagavulin::chooseNextIntent() {
    if (turnCounter_ < 2) {
        intent_.type = INTENT_UNKNOWN;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Sleeping...";
    } else if ((turnCounter_ - 2) % 2 == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = ATTACK_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Attack";
    } else {
        intent_.type = INTENT_DEBUFF;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Siphon Soul";
    }
    turnCounter_ += 1;
}

void Lagavulin::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_DEBUFF) {
        target.applyStatus(STATUS_STRENGTH,  SIPHON_STRENGTH);
        target.applyStatus(STATUS_DEXTERITY, SIPHON_DEXTERITY);
    } else if (intent_.type == INTENT_UNKNOWN) {
        // sleeping, do nothing
    } else {
        Enemy::takeTurn(target, battle);
    }
}
