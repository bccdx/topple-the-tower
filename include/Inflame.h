// include/Inflame.h
#ifndef INFLAME_H
#define INFLAME_H

#include "Card.h"

// permanently increases Strength
class Inflame : public Card {
public:
    Inflame();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int STRENGTH = 2;
};

#endif
