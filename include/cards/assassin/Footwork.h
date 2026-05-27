#ifndef FOOTWORK_H
#define FOOTWORK_H
#include "Card.h"
class Footwork : public Card {
public:
    Footwork();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new Footwork(*this); }
    static const int DEX = 2;
};
#endif
