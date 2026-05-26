// tests/test_deck.cpp
#include "Deck.h"
#include "Strike.h"
#include "Defend.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

Card* makeStrike() { return new Strike(); }
Card* makeDefend() { return new Defend(); }

void test_add_and_draw() {
    Deck d;
    d.addCard(makeStrike());
    d.addCard(makeStrike());
    d.addCard(makeDefend());
    assert(d.drawPileSize() == 3);
    assert(d.handSize() == 0);

    d.draw(2);
    assert(d.handSize() == 2);
    assert(d.drawPileSize() == 1);
    std::cout << "PASSED: test_add_and_draw\n";
}

void test_draw_more_than_available_with_empty_discard() {
    Deck d;
    d.addCard(makeStrike());
    d.draw(5);                       // asked for 5, only 1 available
    assert(d.handSize() == 1);
    assert(d.drawPileSize() == 0);
    std::cout << "PASSED: test_draw_more_than_available_with_empty_discard\n";
}

void test_reshuffle_discard_into_draw() {
    Deck d;
    d.addCard(makeStrike());
    d.addCard(makeDefend());
    d.draw(2);                       // hand: 2, draw: 0
    d.discardHand();                 // discard: 2, hand: 0
    assert(d.discardPileSize() == 2);
    assert(d.drawPileSize() == 0);

    d.draw(2);                       // should reshuffle discard into draw
    assert(d.handSize() == 2);
    assert(d.discardPileSize() == 0);
    std::cout << "PASSED: test_reshuffle_discard_into_draw\n";
}

void test_take_from_hand_moves_ownership() {
    Deck d;
    d.addCard(makeStrike());
    d.draw(1);
    assert(d.handSize() == 1);
    Card* card = d.takeFromHand(0);
    assert(d.handSize() == 0);
    assert(card != 0);
    assert(card->getName() == "Strike");
    delete card;
    std::cout << "PASSED: test_take_from_hand_moves_ownership\n";
}

void test_discard_returns_card_to_discard_pile() {
    Deck d;
    d.addCard(makeStrike());
    d.draw(1);
    Card* card = d.takeFromHand(0);
    d.discard(card);
    assert(d.discardPileSize() == 1);
    std::cout << "PASSED: test_discard_returns_card_to_discard_pile\n";
}

int main() {
    srand(42);   // deterministic for tests
    std::cout << "Running Deck tests...\n\n";
    test_add_and_draw();
    test_draw_more_than_available_with_empty_discard();
    test_reshuffle_discard_into_draw();
    test_take_from_hand_moves_ownership();
    test_discard_returns_card_to_discard_pile();
    std::cout << "\nAll Deck tests passed!\n";
    return 0;
}
