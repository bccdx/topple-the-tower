#include "Cleave.h"

#include "Battle.h"
#include "Hero.h"

Cleave::Cleave()
    : Card("Cleave", "Deal 8 damage.", 1, CARD_ATTACK, TARGET_ENEMY) {
}

void Cleave::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
}

Card* Cleave::clone() const {
    return new Cleave();
}
