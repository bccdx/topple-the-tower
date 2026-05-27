#include "Neutralize.h"
#include "Hero.h"

Neutralize::Neutralize()
    : Card("Neutralize", "Deal 3 damage. Apply 1 Weak.", 0, CARD_ATTACK, TARGET_ENEMY) {}

void Neutralize::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_WEAK, WEAK_STACKS);
}
