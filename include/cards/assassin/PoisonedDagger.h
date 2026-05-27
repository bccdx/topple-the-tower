#ifndef POISONEDDAGGER_H
#define POISONEDDAGGER_H
#include "Card.h"
class PoisonedDagger : public Card {
public:
    PoisonedDagger();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new PoisonedDagger(*this); }
    static const int DAMAGE      = 8;
    static const int WEAK_STACKS = 2;
};
#endif
