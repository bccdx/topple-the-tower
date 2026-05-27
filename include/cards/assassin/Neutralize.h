#ifndef NEUTRALIZE_H
#define NEUTRALIZE_H
#include "Card.h"
class Neutralize : public Card {
public:
    Neutralize();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new Neutralize(*this); }
    static const int DAMAGE     = 3;
    static const int WEAK_STACKS = 1;
};
#endif
