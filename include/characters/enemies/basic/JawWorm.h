// include/characters/enemies/basic/JawWorm.h
#ifndef JAWWORM_H
#define JAWWORM_H

#include "Enemy.h"

// 3-turn cycle: big chomp, thrash (damage + block), bellow (strength + block)
class JawWorm : public Enemy {
public:
    JawWorm();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP    = 42;
    static const int CHOMP_DAMAGE   = 11;
    static const int THRASH_DAMAGE  = 7;
    static const int THRASH_BLOCK   = 5;
    static const int BELLOW_STR     = 3;
    static const int BELLOW_BLOCK   = 6;

private:
    int turnCounter_;
};

#endif
