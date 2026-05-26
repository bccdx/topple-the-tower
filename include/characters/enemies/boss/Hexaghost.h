// include/characters/enemies/boss/Hexaghost.h
#ifndef HEXAGHOST_H
#define HEXAGHOST_H

#include "Enemy.h"

// 3-turn cycle: multi-hit sear, heavier multi-hit inferno, activate (gain strength)
// gains strength each cycle so attacks get stronger over time
class Hexaghost : public Enemy {
public:
    Hexaghost();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP      = 250;
    static const int SEAR_DAMAGE      = 6;   // hits 2
    static const int INFERNO_DAMAGE   = 8;   // hits 3
    static const int ACTIVATE_STR     = 3;

private:
    int turnCounter_;
};

#endif
