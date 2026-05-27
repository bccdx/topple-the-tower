#include "DaggerSpray.h"
#include "Hero.h"

DaggerSpray::DaggerSpray()
    : Card("Dagger Spray", "Deal 4 damage twice.", 1, CARD_ATTACK, TARGET_ENEMY) {}

void DaggerSpray::play(Hero& source, Character& target, Battle& battle) {
    for (int i = 0; i < HITS; i++) {
        source.dealAttackDamage(target, DAMAGE);
    }
}
