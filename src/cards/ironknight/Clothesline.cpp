#include "Clothesline.h"

#include "Battle.h"
#include "Hero.h"

Clothesline::Clothesline()
    : Card("Clothesline", "Deal 12 damage. Apply 1 Weak.", 2, CARD_ATTACK, TARGET_ENEMY) {
}

void Clothesline::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_WEAK, WEAK_STACKS);
}

Card* Clothesline::clone() const {
    return new Clothesline();
}
