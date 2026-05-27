#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "Hero.h"

// agile hero. passive: Ring of the Snake — draw 2 extra cards at the start of each combat
class Assassin : public Hero {
public:
    Assassin();

    static const int STARTING_HP     = 70;
    static const int STARTING_ENERGY = 3;
    static const int NUM_STRIKES     = 5;
    static const int NUM_DEFENDS     = 4;
    static const int NUM_NEUTRALIZES = 1;
};

#endif
