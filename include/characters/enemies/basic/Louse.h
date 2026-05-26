// include/characters/enemies/basic/Louse.h
#ifndef LOUSE_H
#define LOUSE_H

#include "Enemy.h"

// tiny pest. low HP but always attacking
class Louse : public Enemy {
public:
    Louse();
    virtual void chooseNextIntent();

    static const int STARTING_HP   = 16;
    static const int ATTACK_DAMAGE = 5;
};

#endif
