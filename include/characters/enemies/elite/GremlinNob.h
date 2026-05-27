// include/characters/enemies/elite/GremlinNob.h
#ifndef GREMLINNOB_H
#define GREMLINNOB_H

#include "Enemy.h"

// enrages on turn 1 to gain strength, then attacks every turn after
class GremlinNob : public Enemy {
public:
    GremlinNob();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP    = 85;
    static const int ATTACK_DAMAGE  = 14;
    static const int ENRAGE_STR     = 3;

private:
    int turnCounter_;
};

#endif
