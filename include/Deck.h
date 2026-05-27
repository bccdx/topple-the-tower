// include/Deck.h
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

// draw, hand, discard, exhaust piles for one combat. each pile owns its cards
class Deck {
public:
    Deck();
    ~Deck();

    // add a card to the draw pile (used when building the starter deck)
    void addCard(Card* card);

    void shuffleDrawPile();

    // draw n cards. if the draw pile runs out, shuffle the discard back in and keep going
    void draw(int n);

    // dump the hand into discard (end of turn)
    void discardHand();

    // pull a card out of the hand. caller better pass a valid index
    Card* takeFromHand(int handIndex);

    void discard(Card* card);
    void exhaust(Card* card);

    // move hand and discard back to draw pile and shuffle. call between fights
    // exhausted cards stay out for the whole run
    void resetForCombat();

    const std::vector<Card*>& getHand() const        { return hand_; }
    const std::vector<Card*>& getDrawPile() const    { return drawPile_; }
    const std::vector<Card*>& getDiscardPile() const { return discardPile_; }
    const std::vector<Card*>& getExhaustPile() const { return exhaustPile_; }

    int handSize() const        { return (int)hand_.size(); }
    int drawPileSize() const    { return (int)drawPile_.size(); }
    int discardPileSize() const { return (int)discardPile_.size(); }
    int exhaustPileSize() const { return (int)exhaustPile_.size(); }

private:
    std::vector<Card*> drawPile_;
    std::vector<Card*> hand_;
    std::vector<Card*> discardPile_;
    std::vector<Card*> exhaustPile_;
};

#endif
