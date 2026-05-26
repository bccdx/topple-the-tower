#include "JawWorm.h"
#include "Hero.h"

JawWorm::JawWorm() : Enemy("Jaw Worm", STARTING_HP) {
    tier_ = TIER_BASIC;
    turnCounter_ = 0;
    chooseNextIntent();
}

void JawWorm::chooseNextIntent() {
    int phase = turnCounter_ % 3;
    if (phase == 0) {
        intent_.type = INTENT_ATTACK;
        intent_.value = CHOMP_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Chomp";
    } else if (phase == 1) {
        intent_.type = INTENT_ATTACK;
        intent_.value = THRASH_DAMAGE;
        intent_.hits = 1;
        intent_.description = "Thrash";
    } else {
        intent_.type = INTENT_BUFF;
        intent_.value = 0;
        intent_.hits = 1;
        intent_.description = "Bellow";
    }
    turnCounter_ += 1;
}

void JawWorm::takeTurn(Hero& target, Battle& battle) {
    int phase = (turnCounter_ - 1) % 3;
    if (phase == 1) {
        // thrash: deal damage and gain block
        dealAttackDamage(target, THRASH_DAMAGE);
        gainBlock(THRASH_BLOCK);
    } else if (phase == 2) {
        // bellow: gain strength and block
        applyStatus(STATUS_STRENGTH, BELLOW_STR);
        gainBlock(BELLOW_BLOCK);
    } else {
        Enemy::takeTurn(target, battle);
    }
}
