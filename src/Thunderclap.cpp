#include "Thunderclap.h"

#include "Battle.h"
#include "Hero.h"

Thunderclap::Thunderclap()
    : Card("Thunderclap", "Deal 4 damage. Apply 1 Vulnerable.", 1, CARD_ATTACK, TARGET_ENEMY) {
}

void Thunderclap::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_VULNERABLE, VULNERABLE_STACKS);
}

Card* Thunderclap::clone() const {
    return new Thunderclap();
}
