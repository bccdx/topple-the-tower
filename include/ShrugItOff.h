// include/ShrugItOff.h
#ifndef SHRUG_IT_OFF_H
#define SHRUG_IT_OFF_H

#include "Card.h"

// gives block and draws a card
class ShrugItOff : public Card {
public:
    ShrugItOff();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int BLOCK = 8;
    static const int DRAW  = 1;
};

#endif
