#include "Defend.h"

#include "Hero.h"

Defend::Defend() : Card("Defend", "Gain 5 Block.", 1, CARD_SKILL, TARGET_SELF) {}

void Defend::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(BLOCK);
}

Card* Defend::clone() const {
    return new Defend(*this);
}
