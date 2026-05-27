// include/cards/ironknight/TwinStrike.h
#ifndef TWIN_STRIKE_H
#define TWIN_STRIKE_H

#include "Card.h"

// hits twice
class TwinStrike : public Card {
public:
    TwinStrike();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE = 5;
    static const int HITS   = 2;
};

#endif
