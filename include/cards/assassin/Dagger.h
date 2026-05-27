#ifndef DAGGER_H
#define DAGGER_H
#include "Card.h"
class Dagger : public Card {
public:
    Dagger();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new Dagger(*this); }
    static const int DAMAGE = 4;
};
#endif
