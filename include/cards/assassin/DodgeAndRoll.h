#ifndef DODGEANDROLL_H
#define DODGEANDROLL_H
#include "Card.h"
class DodgeAndRoll : public Card {
public:
    DodgeAndRoll();
    virtual void play(Hero& source, Character& target, Battle& battle);
    virtual Card* clone() const { return new DodgeAndRoll(*this); }
    static const int BLOCK = 4;
    static const int DRAW  = 1;
};
#endif
