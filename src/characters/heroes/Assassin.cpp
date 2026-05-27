#include "Assassin.h"

#include "Defend.h"
#include "Neutralize.h"
#include "Relic.h"
#include "Strike.h"

Assassin::Assassin() : Hero("Assassin", STARTING_HP, STARTING_ENERGY) {
    for (int i = 0; i < NUM_STRIKES; i++) {
        deck_.addCard(new Strike());
    }
    for (int i = 0; i < NUM_DEFENDS; i++) {
        deck_.addCard(new Defend());
    }
    for (int i = 0; i < NUM_NEUTRALIZES; i++) {
        deck_.addCard(new Neutralize());
    }
    deck_.shuffleDrawPile();

    addRelic(new Relic(RELIC_RING_OF_THE_SNAKE, "Ring of the Snake", "Draw 2 additional cards at the start of each combat"));
}
