// include/Strike.h
#ifndef STRIKE_H
#define STRIKE_H

#include "Card.h"

// just deals damage
class Strike : public Card {
public:
    Strike();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE = 6;
};

#endif
