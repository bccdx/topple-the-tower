#include "DaggerThrow.h"
#include "Hero.h"

DaggerThrow::DaggerThrow()
    : Card("Dagger Throw", "Deal 9 damage. Draw 1 card.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void DaggerThrow::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    source.getDeck().draw(DRAW);
}
