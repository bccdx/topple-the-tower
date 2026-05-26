#include "ShrugItOff.h"

#include "Battle.h"
#include "Hero.h"

ShrugItOff::ShrugItOff()
    : Card("Shrug It Off", "Gain 8 Block. Draw 1 card.", 1, CARD_SKILL, TARGET_SELF) {
}

void ShrugItOff::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(BLOCK);
    source.getDeck().draw(DRAW);
}

Card* ShrugItOff::clone() const {
    return new ShrugItOff();
}
