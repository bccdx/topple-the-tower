#include "Prepared.h"
#include "Hero.h"

Prepared::Prepared()
    : Card("Prepared", "Draw 1 card.", 0, CARD_SKILL, TARGET_SELF) {}

void Prepared::play(Hero& source, Character& target, Battle& battle) {
    source.getDeck().draw(DRAW);
}
