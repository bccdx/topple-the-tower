#include "DodgeAndRoll.h"
#include "Hero.h"

DodgeAndRoll::DodgeAndRoll()
    : Card("Dodge and Roll", "Gain 4 Block. Draw 1 card.", 1, CARD_SKILL, TARGET_SELF) {}

void DodgeAndRoll::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(BLOCK);
    source.getDeck().draw(DRAW);
}
