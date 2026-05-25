// include/Ironknight.h
#ifndef IRONKNIGHT_H
#define IRONKNIGHT_H

#include "Hero.h"

// first playable hero. melee bruiser, Strike/Defend starter
class Ironknight : public Hero {
public:
    Ironknight();

    static const int STARTING_HP     = 80;
    static const int STARTING_ENERGY = 3;
    static const int NUM_STRIKES     = 5;
    static const int NUM_DEFENDS     = 5;
};

#endif
