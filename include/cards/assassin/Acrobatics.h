#ifndef ACROBATICS_H
#define ACROBATICS_H
#include "Card.h"
class Acrobatics : public Card {
public:
    Acrobatics();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new Acrobatics(*this); }
    static const int DRAW = 3;
};
#endif
