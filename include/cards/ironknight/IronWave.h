// include/cards/ironknight/IronWave.h
#ifndef IRON_WAVE_H
#define IRON_WAVE_H

#include "Card.h"

// deals damage and gives block in one card
class IronWave : public Card {
public:
    IronWave();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;

    static const int DAMAGE = 5;
    static const int BLOCK  = 5;
};

#endif
