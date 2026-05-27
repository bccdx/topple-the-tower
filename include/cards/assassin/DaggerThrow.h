#ifndef DAGGERTHROW_H
#define DAGGERTHROW_H
#include "Card.h"
class DaggerThrow : public Card {
public:
    DaggerThrow();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new DaggerThrow(*this); }
    static const int DAMAGE = 9;
    static const int DRAW   = 1;
};
#endif
