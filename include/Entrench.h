// include/Entrench.h
#ifndef ENTRENCH_H
#define ENTRENCH_H

#include "Card.h"

// doubles current block
class Entrench : public Card {
public:
    Entrench();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;
};

#endif
