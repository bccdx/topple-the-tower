// include/Relic.h
#ifndef RELIC_H
#define RELIC_H

#include <string>

// passive item the hero carries. effect is stubbed for now, just stores name + description
class Relic {
public:
    Relic(const std::string& name, const std::string& description);

    const std::string& getName() const        { return name_; }
    const std::string& getDescription() const { return description_; }

private:
    std::string name_;
    std::string description_;
};

#endif
