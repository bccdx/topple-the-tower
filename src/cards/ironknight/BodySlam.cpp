#include "BodySlam.h"

#include "Battle.h"
#include "Hero.h"

BodySlam::BodySlam()
    : Card("Body Slam", "Deal damage equal to your current Block.", 1, CARD_ATTACK, TARGET_ENEMY) {
}

void BodySlam::play(Hero& source, Character& target, Battle& battle) {
    source.dealAttackDamage(target, source.getBlock());
}

Card* BodySlam::clone() const {
    return new BodySlam();
}
