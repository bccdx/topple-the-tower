#include "Bash.h"

#include "Character.h"
#include "Hero.h"

Bash::Bash() : Card("Bash", "Deal 8 damage. Apply 2 Vulnerable.", 2, CARD_ATTACK, TARGET_ENEMY) {}

void Bash::play(Hero& source, Character& target, Battle& battle) {
    // damage resolves first so Bash's own Vulnerable doesn't amplify itself
    source.dealAttackDamage(target, DAMAGE);
    target.applyStatus(STATUS_VULNERABLE, VULNERABLE_STACKS);
}

Card* Bash::clone() const {
    return new Bash(*this);
}
