#include "SpikeSlime.h"
#include "Hero.h"

SpikeSlime::SpikeSlime() : Enemy("Spike Slime", STARTING_HP) {
    tier_ = TIER_BASIC;
    turnCounter_ = 0;
    chooseNextIntent();
}

void SpikeSlime::chooseNextIntent() {
    if (turnCounter_ % 2 == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = TACKLE_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Flame Tackle";
    } else {
        intent_.type = INTENT_DEBUFF;
        intent_.value = LICK_FRAIL;
        intent_.hits = 1;
        intent_.description = "Lick";
    }
    turnCounter_ += 1;
}

void SpikeSlime::takeTurn(Hero& target, Battle& battle) {
    if (intent_.type == INTENT_DEBUFF) {
        target.applyStatus(STATUS_FRAIL, LICK_FRAIL);
    } else {
        Enemy::takeTurn(target, battle);
    }
}
