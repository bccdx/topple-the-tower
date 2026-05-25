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
    int getBlock() const { return block_; }
    bool isAlive() const { return currentHp_ > 0; }

    // stat mutations
    void takeDamage(int amount);     // respects current Block
    void gainBlock(int amount);
    void heal(int amount);

    // applies attacker logic, then hits target. returns HP lost
    int dealAttackDamage(Character& target, int baseDamage);

    // turn lifecycle hooks (overridable)
    virtual void onTurnStart();      // clears Block by default
    virtual void onTurnEnd();        // no-op for now

protected:
    std::string name_;
    int maxHp_;
    int currentHp_;
    int block_;
};

#endif
