// include/characters/enemies/elite/TowerGuard.h
#ifndef TOWERGUARD_H
#define TOWERGUARD_H

#include "Enemy.h"

// elite guard. alternates between a big hit and shield up
class TowerGuard : public Enemy {
public:
    TowerGuard();
    virtual void chooseNextIntent();

    static const int STARTING_HP   = 90;
    static const int ATTACK_DAMAGE = 15;
    static const int DEFEND_BLOCK  = 12;

private:
    int turnCounter_;
};

#endif
