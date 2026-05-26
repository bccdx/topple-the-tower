// include/cards/ironknight/Thunderclap.h
#ifndef THUNDERCLAP_H
#define THUNDERCLAP_H

#include "Card.h"

// deals damage and applies Vulnerable
class Thunderclap : public Card {
public:
    Thunderclap();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE             = 4;
    static const int VULNERABLE_STACKS  = 1;
};

#endif
