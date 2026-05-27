// include/Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

// all the statuses we track. Weak/Frail/Vulnerable tick down each turn,
// Strength/Dexterity stick around the whole fight, Artifact eats one debuff.
// STATUS_COUNT is a sentinel for the size of the statuses array.
enum StatusType {
    STATUS_WEAK,
    STATUS_FRAIL,
    STATUS_VULNERABLE,
    STATUS_STRENGTH,
    STATUS_DEXTERITY,
    STATUS_ARTIFACT,
    STATUS_COUNT
};

std::string statusToString(StatusType s);
bool isDebuff(StatusType s);
bool ticksDownEachTurn(StatusType s);

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

    // statuses
    int getStatus(StatusType s) const;
    void applyStatus(StatusType s, int amount);
    void removeStatus(StatusType s);

    // stat mutations
    void takeDamage(int amount);     // respects current Block
    void takeHpLoss(int amount);     // bypasses Block
    void gainBlock(int amount);      // respects Dexterity / Frail
    void heal(int amount);

    // factors in attacker's Strength/Weak and target's Vulnerable, then hits. returns HP lost
    int dealAttackDamage(Character& target, int baseDamage);

    // turn lifecycle hooks (overridable)
    virtual void onTurnStart();      // clears Block by default
    virtual void onTurnEnd();        // ticks down turn-based debuffs

protected:
    std::string name_;
    int maxHp_;
    int currentHp_;
    int block_;
    int statuses_[STATUS_COUNT];
};

#endif
