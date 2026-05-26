// include/PommelStrike.h
#ifndef POMMEL_STRIKE_H
#define POMMEL_STRIKE_H

#include "Card.h"

// deals damage and draws a card
class PommelStrike : public Card {
public:
    PommelStrike();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE = 9;
    static const int DRAW   = 1;
};

#endif
