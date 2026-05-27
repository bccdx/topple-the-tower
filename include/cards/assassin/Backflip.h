#ifndef BACKFLIP_H
#define BACKFLIP_H
#include "Card.h"
class Backflip : public Card {
public:
    Backflip();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new Backflip(*this); }
    static const int BLOCK = 5;
    static const int DRAW  = 2;
};
#endif
