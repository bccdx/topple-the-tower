#include "Inflame.h"

#include "Battle.h"
#include "Hero.h"

Inflame::Inflame()
    : Card("Inflame", "Gain 2 Strength.", 1, CARD_POWER, TARGET_SELF) {
}

void Inflame::play(Hero& source, Character& target, Battle& battle) {
    source.applyStatus(STATUS_STRENGTH, STRENGTH);
}

Card* Inflame::clone() const {
    return new Inflame();
}
