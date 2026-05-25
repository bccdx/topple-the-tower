// include/Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    Character(const std::string& name, int maxHp);
    virtual ~Character() {}

    // identity / stats
    const std::string& getName() const { return name_; }
    int getMaxHp() const { return maxHp_; }
    int getCurrentHp() const { return currentHp_; }
    bool isAlive() const { return currentHp_ > 0; }

    // stat mutations
    void takeDamage(int amount);
    void heal(int amount);

protected:
    std::string name_;
    int maxHp_;
    int currentHp_;
};

#endif
