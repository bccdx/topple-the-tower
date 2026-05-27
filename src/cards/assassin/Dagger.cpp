#include "Dagger.h"
#include "Hero.h"

Dagger::Dagger() : Card("Dagger", "Deal 4 damage.", 0, CARD_ATTACK, TARGET_ENEMY) {}

void Dagger::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
}
