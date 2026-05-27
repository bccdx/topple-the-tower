// include/Ironknight.h
#ifndef IRONKNIGHT_H
#define IRONKNIGHT_H

#include "Hero.h"

// melee bruiser with Strike/Defend/Bash starter deck.
// passive: heals 6 HP at the end of each combat (Burning Blood)
class Ironknight : public Hero {
public:
    Ironknight();
    virtual void onCombatEnd();

    static const int STARTING_HP     = 80;
    static const int STARTING_ENERGY = 3;
    static const int NUM_STRIKES     = 5;
    static const int NUM_DEFENDS     = 4;
    static const int NUM_BASHES      = 1;
    static const int COMBAT_END_HEAL = 6;
};

#endif
