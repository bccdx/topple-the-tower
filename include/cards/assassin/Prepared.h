#ifndef PREPARED_H
#define PREPARED_H
#include "Card.h"
class Prepared : public Card {
public:
    Prepared();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new Prepared(*this); }
    static const int DRAW = 1;
};
#endif
