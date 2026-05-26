// include/Cleave.h
#ifndef CLEAVE_H
#define CLEAVE_H

#include "Card.h"

class Cleave : public Card {
public:
    Cleave();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE = 8;
};

#endif
