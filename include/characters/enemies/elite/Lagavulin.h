// include/characters/enemies/elite/Lagavulin.h
#ifndef LAGAVULIN_H
#define LAGAVULIN_H

#include "Enemy.h"

// sleeps for the first 2 turns, then alternates heavy attacks with Siphon Soul
// (siphon soul drains the hero's Strength and Dexterity)
class Lagavulin : public Enemy {
public:
    Lagavulin();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP      = 109;
    static const int ATTACK_DAMAGE    = 20;
    static const int SIPHON_STRENGTH  = -2;
    static const int SIPHON_DEXTERITY = -2;

private:
    int turnCounter_;
};

#endif
