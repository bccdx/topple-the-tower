#include "Strike.h"

#include "Character.h"
#include "Hero.h"

Strike::Strike() : Card("Strike", "Deal 6 damage.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void Strike::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
}

Card* Strike::clone() const {
    return new Strike(*this);
}
