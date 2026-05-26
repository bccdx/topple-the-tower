// include/characters/enemies/elite/BruteGuard.h
#ifndef BRUTEGUARD_H
#define BRUTEGUARD_H

#include "Enemy.h"

// mid-tower enemy. alternates between a heavy swing and raising a shield
class BruteGuard : public Enemy {
public:
    BruteGuard();
    virtual void chooseNextIntent();

    static const int STARTING_HP   = 80;
    static const int ATTACK_DAMAGE = 14;
    static const int DEFEND_BLOCK  = 10;

private:
    int turnCounter_;
};

#endif
