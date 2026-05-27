#include "IronWave.h"

#include "Battle.h"
#include "Hero.h"

IronWave::IronWave()
    : Card("Iron Wave", "Deal 5 damage. Gain 5 Block.", 1, CARD_ATTACK, TARGET_ENEMY) {
}

void IronWave::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    source.gainBlock(BLOCK);
}

Card* IronWave::clone() const {
    return new IronWave();
}
