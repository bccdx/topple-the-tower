// include/characters/enemies/basic/Slime.h
#ifndef SLIME_H
#define SLIME_H

#include "Enemy.h"

// weak first-floor enemy. attacks every turn
class Slime : public Enemy {
public:
    Slime();
    virtual void chooseNextIntent();

    static const int STARTING_HP   = 28;
    static const int ATTACK_DAMAGE = 8;
};

#endif
