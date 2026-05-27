// include/Defend.h
#ifndef DEFEND_H
#define DEFEND_H

#include "Card.h"

// gives the player some Block
class Defend : public Card {
public:
    Defend();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int BLOCK = 5;
};

#endif
