// include/characters/enemies/elite/GoblinArcher.h
#ifndef GOBLINARCHER_H
#define GOBLINARCHER_H

#include "Enemy.h"

// alternates a single arrow with a volley of two quick shots
class GoblinArcher : public Enemy {
public:
    GoblinArcher();
    virtual void chooseNextIntent();

    static const int STARTING_HP    = 80;
    static const int ARROW_DAMAGE   = 10;
    static const int VOLLEY_DAMAGE  = 6;  // hits twice

private:
    int turnCounter_;
};

#endif
