#include "PoisonedDagger.h"
#include "Hero.h"

PoisonedDagger::PoisonedDagger()
    : Card("Poisoned Dagger", "Deal 8 damage. Apply 2 Weak.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void PoisonedDagger::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_WEAK, WEAK_STACKS);
}
