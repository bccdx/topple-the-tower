// include/Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

#include <string>

class Hero;
class Battle;

// enemies telegraph their next move so the player can plan
enum IntentType { INTENT_ATTACK, INTENT_DEFEND, INTENT_BUFF, INTENT_DEBUFF, INTENT_UNKNOWN };

struct Intent {
    IntentType type;
    int value;                // damage for INTENT_ATTACK, Block for INTENT_DEFEND, etc
    int hits;                 // for multi-hit attacks
    std::string description;  // flavor text shown next to the icon

    Intent() {
        type = INTENT_UNKNOWN;
        value = 0;
        hits = 1;
    }
};

std::string intentTypeToString(IntentType t);

class Enemy : public Character {
public:
    Enemy(const std::string& name, int maxHp);

    const Intent& getIntent() const { return intent_; }

    // decide what the enemy will do next. called at construction and after each
    // enemy turn so the player can always see the intent
    virtual void chooseNextIntent() = 0;

    // run the current intent. default handles plain ATTACK/DEFEND. fancier enemies should override
    virtual void takeTurn(Hero& target, Battle& battle);

protected:
    Intent intent_;
};

#endif
