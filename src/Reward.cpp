#include "Reward.h"

#include "Hero.h"
#include "Relic.h"

#include "Bash.h"
#include "BodySlam.h"
#include "Cleave.h"
#include "Clothesline.h"
#include "Defend.h"
#include "Entrench.h"
#include "Inflame.h"
#include "IronWave.h"
#include "PommelStrike.h"
#include "ShrugItOff.h"
#include "Strike.h"
#include "Thunderclap.h"
#include "TwinStrike.h"

#include <cstdlib>
#include <string>

Reward::Reward() {
    gold_ = 0;
}

Reward::~Reward() {
    for (int i = 0; i < (int)options_.size(); i++) {
        delete options_[i];
    }
}

void Reward::setGold(int amount) {
    gold_ = amount;
}

void Reward::awardRelic(Hero& hero) {
    // pool of all obtainable relics
    std::string names[] = {
        "Burning Blood",
        "Vajra",
        "Anchor",
        "Bronze Scales",
        "Bag of Marbles",
        "Centennial Puzzle",
        "Red Skull",
        "Meat on the Bone",
        "Oddly Smooth Stone",
        "Paper Krane"
    };
    std::string descs[] = {
        "At the start of combat, heal 6 HP",
        "Gain 1 Strength at the start of each combat",
        "Start each combat with 10 Block",
        "Whenever you take damage, deal 3 back",
        "At the start of combat, apply 1 Vulnerable to all enemies",
        "First time you lose HP each combat, draw 3 cards",
        "While HP is at or below 50%, gain 3 Strength",
        "If HP is at or below 50% at end of combat, heal 12 HP",
        "At the start of each combat, gain 1 Dexterity",
        "Reduce all incoming attack damage by 1"
    };
    int poolSize = 10;
    int idx = rand() % poolSize;
    hero.addRelic(new Relic(names[idx], descs[idx]));
}

void Reward::generateOptions(int n) {
    // clear any previous options
    for (int i = 0; i < (int)options_.size(); i++) {
        delete options_[i];
    }
    options_.clear();

    // pool of obtainable cards
    std::vector<Card*> pool;
    pool.push_back(new IronWave());
    pool.push_back(new Cleave());
    pool.push_back(new PommelStrike());
    pool.push_back(new ShrugItOff());
    pool.push_back(new Clothesline());
    pool.push_back(new TwinStrike());
    pool.push_back(new Thunderclap());
    pool.push_back(new Inflame());
    pool.push_back(new BodySlam());
    pool.push_back(new Entrench());

    // Fisher-Yates shuffle
    for (int i = (int)pool.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* tmp = pool[i];
        pool[i] = pool[j];
        pool[j] = tmp;
    }

    // take first n (or all if n > pool size)
    int take = n < (int)pool.size() ? n : (int)pool.size();
    for (int i = 0; i < take; i++) {
        options_.push_back(pool[i]);
    }
    // delete the rest
    for (int i = take; i < (int)pool.size(); i++) {
        delete pool[i];
    }
}

bool Reward::pickCard(int index, Hero& hero) {
    if (index < 0 || index >= (int)options_.size()) return false;
    hero.getDeck().addCard(options_[index]);
    options_[index] = NULL;
    return true;
}
