#include "PommelStrike.h"

#include "Battle.h"
#include "Hero.h"

PommelStrike::PommelStrike()
    : Card("Pommel Strike", "Deal 9 damage. Draw 1 card.", 1, CARD_ATTACK, TARGET_ENEMY) {
}

void PommelStrike::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    source.getDeck().draw(DRAW);
}

Card* PommelStrike::clone() const {
    return new PommelStrike();
}
