// include/characters/enemies/elite/StoneKnight.h
#ifndef STONEKNIGHT_H
#define STONEKNIGHT_H

#include "Enemy.h"

// slow but hits hard. 3-turn cycle: attack, defend, heavy attack
class StoneKnight : public Enemy {
public:
    StoneKnight();
    virtual void chooseNextIntent();

    static const int STARTING_HP      = 110;
    static const int ATTACK_DAMAGE    = 9;
    static const int HEAVY_DAMAGE     = 16;
    static const int DEFEND_BLOCK     = 12;

private:
    int turnCounter_;
};

#endif
