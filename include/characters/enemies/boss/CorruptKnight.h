// include/characters/enemies/boss/CorruptKnight.h
#ifndef CORRUPTKNIGHT_H
#define CORRUPTKNIGHT_H

#include "Enemy.h"

// final boss of a longer run. 4-turn cycle with escalating attacks
class CorruptKnight : public Enemy {
public:
    CorruptKnight();
    virtual void chooseNextIntent();

    static const int STARTING_HP   = 150;
    static const int ATTACK_A      = 16;
    static const int ATTACK_B      = 16;
    static const int DEFEND_BLOCK  = 12;
    static const int ATTACK_C      = 22;

private:
    int turnCounter_;
};

#endif
