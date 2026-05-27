#include "Backflip.h"
#include "Hero.h"

Backflip::Backflip()
    : Card("Backflip", "Gain 5 Block. Draw 2 cards.", 1, CARD_SKILL, TARGET_SELF) {}

void Backflip::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(BLOCK);
    source.getDeck().draw(DRAW);
}
