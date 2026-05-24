#include "Deck.h"

#include <cstdlib>

Deck::Deck() {
}

Deck::~Deck() {
    // delete every card the deck owns
    for (int i = 0; i < (int)drawPile_.size(); i++) {
        delete drawPile_[i];
    }
    for (int i = 0; i < (int)hand_.size(); i++) {
        delete hand_[i];
    }
    for (int i = 0; i < (int)discardPile_.size(); i++) {
        delete discardPile_[i];
    }
    for (int i = 0; i < (int)exhaustPile_.size(); i++) {
        delete exhaustPile_[i];
    }
}

void Deck::addCard(Card* card) {
    drawPile_.push_back(card);
}

void Deck::shuffleDrawPile() {
    // Fisher-Yates shuffle
    int n = (int)drawPile_.size();
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* temp = drawPile_[i];
        drawPile_[i] = drawPile_[j];
        drawPile_[j] = temp;
    }
}

void Deck::draw(int n) {
    for (int i = 0; i < n; i++) {
        if (drawPile_.size() == 0) {
            if (discardPile_.size() == 0) return;
            // move discard into draw, then reshuffle
            for (int j = 0; j < (int)discardPile_.size(); j++) {
                drawPile_.push_back(discardPile_[j]);
            }
            discardPile_.clear();
            shuffleDrawPile();
        }
        hand_.push_back(drawPile_.back());
        drawPile_.pop_back();
    }
}

void Deck::discardHand() {
    for (int i = 0; i < (int)hand_.size(); i++) {
        discardPile_.push_back(hand_[i]);
    }
    hand_.clear();
}

Card* Deck::takeFromHand(int handIndex) {
    Card* card = hand_[handIndex];
    // shift the rest of the hand down by one
    for (int i = handIndex; i < (int)hand_.size() - 1; i++) {
        hand_[i] = hand_[i + 1];
    }
    hand_.pop_back();
    return card;
}

void Deck::discard(Card* card) {
    discardPile_.push_back(card);
}

void Deck::exhaust(Card* card) {
    exhaustPile_.push_back(card);
}
