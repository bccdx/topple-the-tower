// include/TowerGuard.h
#ifndef TOWERGUARD_H
#define TOWERGUARD_H

#include "Enemy.h"

// first enemy. alternates between a big hit and shield up
class TowerGuard : public Enemy {
public:
    TowerGuard();
    virtual void chooseNextIntent();

    static const int STARTING_HP   = 40;
    static const int ATTACK_DAMAGE = 12;
    static const int DEFEND_BLOCK  = 8;

private:
    int turnCounter_;
};

#endif
