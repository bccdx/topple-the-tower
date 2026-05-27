// include/cards/ironknight/Bash.h
#ifndef BASH_H
#define BASH_H

#include "Card.h"

// heavy hit that also applies Vulnerable
class Bash : public Card {
public:
    Bash();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE = 8;
    static const int VULNERABLE_STACKS = 2;
};

#endif
