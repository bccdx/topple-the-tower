#include "Ironknight.h"

#include "Bash.h"
#include "Defend.h"
#include "Strike.h"

void Ironknight::onCombatEnd() {
    Hero::onCombatEnd();    // relic effects first
    heal(COMBAT_END_HEAL);
}

Ironknight::Ironknight() : Hero("Ironknight", STARTING_HP, STARTING_ENERGY) {
    for (int i = 0; i < NUM_STRIKES; i++) {
        deck_.addCard(new Strike());
    }
    for (int i = 0; i < NUM_DEFENDS; i++) {
        deck_.addCard(new Defend());
    }
    for (int i = 0; i < NUM_BASHES; i++) {
        deck_.addCard(new Bash());
    }
    deck_.shuffleDrawPile();
}
