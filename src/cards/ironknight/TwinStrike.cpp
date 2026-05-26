#include "TwinStrike.h"

#include "Battle.h"
#include "Hero.h"

TwinStrike::TwinStrike()
    : Card("Twin Strike", "Deal 5 damage twice.", 1, CARD_ATTACK, TARGET_ENEMY) {
}

void TwinStrike::play(Hero& source, Character& target, Battle& battle) {
    for (int i = 0; i < HITS; i++) {
        source.dealAttackDamage(target, DAMAGE);
    }
}

Card* TwinStrike::clone() const {
    return new TwinStrike();
}
