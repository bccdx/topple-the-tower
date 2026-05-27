// include/Reward.h
#ifndef REWARD_H
#define REWARD_H

#include "Card.h"
#include <vector>

class Hero;

// generates post-battle rewards: gold (automatic), a relic (automatic), and card choices (player picks one or skips)
class Reward {
public:
    Reward();
    ~Reward();

    void setGold(int amount);
    void awardRelic(Hero& hero);        // picks a random relic from the pool and gives it to the hero
    void generateOptions(int n, const Hero& hero);  // fill options_ with n random cards from the hero's pool
    bool pickCard(int index, Hero& hero); // returns false if index is out of range

    int getGold() const                        { return gold_; }
    const std::vector<Card*>& getOptions() const { return options_; }
    int optionCount() const                    { return (int)options_.size(); }

private:
    std::vector<Card*> options_;
    int gold_;
};

#endif
