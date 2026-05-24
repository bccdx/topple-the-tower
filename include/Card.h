// include/Card.h
#ifndef CARD_H
#define CARD_H

#include <string>

class Hero;
class Character;
class Battle;

enum CardType { CARD_ATTACK, CARD_SKILL, CARD_POWER };
enum CardTarget { TARGET_ENEMY, TARGET_SELF, TARGET_NONE };

std::string cardTypeToString(CardType t);

// base class for every Card
class Card {
public:
    Card(const std::string& name,
         const std::string& description,
         int cost,
         CardType type,
         CardTarget targetType);
    virtual ~Card() {}

    const std::string& getName() const        { return name_; }
    const std::string& getDescription() const { return description_; }
    int getCost() const                       { return cost_; }
    CardType getType() const                  { return type_; }
    CardTarget getTargetType() const          { return targetType_; }

    // subclasses do the actual effect. for TARGET_SELF cards you can just pass source as target
    virtual void play(Hero& source, Character& target, Battle& battle) = 0;

    // copy used when building decks from templates
    virtual Card* clone() const = 0;

protected:
    std::string name_;
    std::string description_;
    int cost_;
    CardType type_;
    CardTarget targetType_;
};

#endif
