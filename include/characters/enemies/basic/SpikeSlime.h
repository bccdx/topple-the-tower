// include/characters/enemies/basic/SpikeSlime.h
#ifndef SPIKESLIME_H
#define SPIKESLIME_H

#include "Enemy.h"

// alternates a tackle attack with a lick that applies Frail
class SpikeSlime : public Enemy {
public:
    SpikeSlime();
    virtual void chooseNextIntent();
    virtual void takeTurn(Hero& target, Battle& battle);

    static const int STARTING_HP    = 32;
    static const int TACKLE_DAMAGE  = 8;
    static const int LICK_FRAIL     = 1;

private:
    int turnCounter_;
};

#endif
