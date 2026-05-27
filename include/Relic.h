// include/Relic.h
#ifndef RELIC_H
#define RELIC_H

#include <string>

enum RelicType {
    RELIC_BURNING_BLOOD,
    RELIC_VAJRA,
    RELIC_ANCHOR,
    RELIC_BRONZE_SCALES,
    RELIC_BAG_OF_MARBLES,
    RELIC_CENTENNIAL_PUZZLE,
    RELIC_RED_SKULL,
    RELIC_MEAT_ON_THE_BONE,
    RELIC_ODDLY_SMOOTH_STONE,
    RELIC_PAPER_KRANE,
    RELIC_RING_OF_THE_SNAKE
};

class Relic {
public:
    Relic(RelicType type, const std::string& name, const std::string& description);

    RelicType getRelicType() const              { return type_; }
    const std::string& getName() const          { return name_; }
    const std::string& getDescription() const   { return description_; }

private:
    RelicType type_;
    std::string name_;
    std::string description_;
};

#endif
