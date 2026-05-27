#include "Footwork.h"
#include "Hero.h"

Footwork::Footwork()
    : Card("Footwork", "Gain 2 Dexterity.", 1, CARD_POWER, TARGET_SELF) {}

void Footwork::play(Hero& source, Character& target, Battle& battle) {
    source.applyStatus(STATUS_DEXTERITY, DEX);
}
