#include "Entrench.h"

#include "Battle.h"
#include "Hero.h"

Entrench::Entrench()
    : Card("Entrench", "Gain Block equal to your current Block.", 2, CARD_SKILL, TARGET_SELF) {
}

void Entrench::play(Hero& source, Character& target, Battle& battle) {
    source.gainBlock(source.getBlock());
}

Card* Entrench::clone() const {
    return new Entrench();
}
