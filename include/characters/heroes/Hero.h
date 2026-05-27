// include/Hero.h
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Deck.h"
#include "Relic.h"
#include <vector>

// base for all player characters. owns a Deck, tracks Energy
class Hero : public Character {
public:
    Hero(const std::string& name, int maxHp, int maxEnergy);
    virtual ~Hero();

    int getMaxEnergy() const     { return maxEnergy_; }
    int getCurrentEnergy() const { return currentEnergy_; }
    void spendEnergy(int amount);
    void gainEnergy(int amount);

    Deck& getDeck()             { return deck_; }
    const Deck& getDeck() const { return deck_; }

    void earnGold(int amount);
    int  getGold() const { return gold_; }

    void addRelic(Relic* relic);   // hero takes ownership
    const std::vector<Relic*>& getRelics() const { return relics_; }

    // reset Block + Energy, draw a fresh hand
    virtual void onTurnStart();
    // discard the hand, then tick down statuses
    virtual void onTurnEnd();

    static const int DEFAULT_DRAW = 5;

protected:
    int maxEnergy_;
    int currentEnergy_;
    Deck deck_;
    int gold_;
    std::vector<Relic*> relics_;
};

#endif
