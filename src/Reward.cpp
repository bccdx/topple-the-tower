#include "Reward.h"

#include "Hero.h"
#include "Relic.h"

// ironknight cards
#include "BodySlam.h"
#include "Cleave.h"
#include "Clothesline.h"
#include "Entrench.h"
#include "Inflame.h"
#include "IronWave.h"
#include "PommelStrike.h"
#include "ShrugItOff.h"
#include "Thunderclap.h"
#include "TwinStrike.h"

// assassin cards
#include "Acrobatics.h"
#include "Backflip.h"
#include "Dagger.h"
#include "DaggerSpray.h"
#include "DaggerThrow.h"
#include "DodgeAndRoll.h"
#include "Footwork.h"
#include "Neutralize.h"
#include "PoisonedDagger.h"
#include "Prepared.h"

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
    struct RelicInfo {
        RelicType type;
        const char* name;
        const char* desc;
    };
    RelicInfo pool[] = {
        { RELIC_BURNING_BLOOD,     "Burning Blood",     "At the start of combat, heal 6 HP" },
        { RELIC_VAJRA,             "Vajra",             "Gain 1 Strength at the start of each combat" },
        { RELIC_ANCHOR,            "Anchor",            "Start each combat with 10 Block" },
        { RELIC_BRONZE_SCALES,     "Bronze Scales",     "Whenever you lose HP, deal 3 damage back" },
        { RELIC_BAG_OF_MARBLES,    "Bag of Marbles",    "At the start of combat, apply 1 Vulnerable to the enemy" },
        { RELIC_CENTENNIAL_PUZZLE, "Centennial Puzzle", "First time you lose HP each combat, draw 3 cards" },
        { RELIC_RED_SKULL,         "Red Skull",         "While HP is at or below 50%, gain 3 Strength" },
        { RELIC_MEAT_ON_THE_BONE,  "Meat on the Bone",  "If HP is at or below 50% at end of combat, heal 12 HP" },
        { RELIC_ODDLY_SMOOTH_STONE,"Oddly Smooth Stone","At the start of each combat, gain 1 Dexterity" },
        { RELIC_PAPER_KRANE,       "Paper Krane",       "Reduce all incoming attack damage by 1" }
    };
    int poolSize = 10;
    int idx = rand() % poolSize;
    hero.addRelic(new Relic(pool[idx].type, pool[idx].name, pool[idx].desc));
}

void Reward::generateOptions(int n, const Hero& hero) {
    for (int i = 0; i < (int)options_.size(); i++) {
        delete options_[i];
    }
    options_.clear();

    std::vector<Card*> pool;

    if (hero.getName() == "Assassin") {
        pool.push_back(new Dagger());
        pool.push_back(new Neutralize());
        pool.push_back(new Acrobatics());
        pool.push_back(new DaggerSpray());
        pool.push_back(new DaggerThrow());
        pool.push_back(new DodgeAndRoll());
        pool.push_back(new Footwork());
        pool.push_back(new Prepared());
        pool.push_back(new Backflip());
        pool.push_back(new PoisonedDagger());
    } else {
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
    }

    for (int i = (int)pool.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card* tmp = pool[i];
        pool[i] = pool[j];
        pool[j] = tmp;
    }

    int take = n < (int)pool.size() ? n : (int)pool.size();
    for (int i = 0; i < take; i++) {
        options_.push_back(pool[i]);
    }
    for (int i = take; i < (int)pool.size(); i++) {
        delete pool[i];
    }
}

bool Reward::pickCard(int index, Hero& hero) {
    if (index < 0 || index >= (int)options_.size()) return false;
    if (options_[index] == NULL) return false;  // already picked
    hero.getDeck().addCard(options_[index]);
    options_[index] = NULL;
    return true;
}
