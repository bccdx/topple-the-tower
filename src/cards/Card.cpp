#include "Card.h"

std::string cardTypeToString(CardType t) {
    switch (t) {
        case CARD_ATTACK: return "Attack";
        case CARD_SKILL:  return "Skill";
        case CARD_POWER:  return "Power";
    }
    return "?";
}

Card::Card(const std::string& name,
           const std::string& description,
           int cost,
           CardType type,
           CardTarget targetType) {
    name_ = name;
    description_ = description;
    cost_ = cost;
    type_ = type;
    targetType_ = targetType;
}
