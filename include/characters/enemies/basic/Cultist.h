// include/characters/enemies/basic/Cultist.h
#ifndef CULTIST_H
#define CULTIST_H

#include "Enemy.h"

// alternates between a ritual that gains Strength and a dark strike.
// gets stronger every time it performs the ritual
class Cultist : public Enemy {
public:
    Cultist();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP   = 50;
    static const int ATTACK_DAMAGE = 6;
    static const int RITUAL_STRENGTH = 3;  // strength gained per incantation

private:
    int turnCounter_;
};

#endif
