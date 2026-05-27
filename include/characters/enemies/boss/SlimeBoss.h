// include/characters/enemies/boss/SlimeBoss.h
#ifndef SLIMEBOSS_H
#define SLIMEBOSS_H

#include "Enemy.h"

// alternates a massive slam with a goop that applies Weak and Frail
class SlimeBoss : public Enemy {
public:
    SlimeBoss();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP   = 140;
    static const int SLAM_DAMAGE   = 30;
    static const int GOOP_WEAK     = 2;
    static const int GOOP_FRAIL    = 2;

private:
    int turnCounter_;
};

#endif
