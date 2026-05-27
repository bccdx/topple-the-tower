// include/cards/ironknight/BodySlam.h
#ifndef BODY_SLAM_H
#define BODY_SLAM_H

#include "Card.h"

// deals damage equal to the hero's current block
class BodySlam : public Card {
public:
    BodySlam();
    void play(Hero& source, Character& target, Battle& battle);
    Card* clone() const;
};

#endif
