#include "Acrobatics.h"
#include "Hero.h"

Acrobatics::Acrobatics()
    : Card("Acrobatics", "Draw 3 cards.", 1, CARD_SKILL, TARGET_SELF) {}

void Acrobatics::play(Hero& source, Character& target, Battle& battle) {
    source.getDeck().draw(DRAW);
}
