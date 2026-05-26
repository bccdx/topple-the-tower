// include/cards/ironknight/Clothesline.h
#ifndef CLOTHESLINE_H
#define CLOTHESLINE_H

#include "Card.h"

// heavy hit that also applies Weak
class Clothesline : public Card {
public:
    Clothesline();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE      = 12;
    static const int WEAK_STACKS = 1;
};

#endif
