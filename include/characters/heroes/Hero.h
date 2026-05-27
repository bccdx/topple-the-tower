// include/Hero.h
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Deck.h"
#include "Relic.h"
#include <vector>

class Enemy;

enum HeroType { HERO_IRONKNIGHT, HERO_ASSASSIN };

// base for all player characters. owns a Deck, tracks Energy
class Hero : public Character {
public:
    Hero(const std::string& name, int maxHp, int maxEnergy);
    virtual ~Hero();

    virtual HeroType getHeroType() const { return HERO_IRONKNIGHT; }

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
    // called at the start of combat. applies relic effects that trigger on combat start
    virtual void onCombatStart(Enemy& enemy);
    // called after winning a combat. handles relic end-of-combat effects
    virtual void onCombatEnd();

    // override: applies Paper Krane reduction, triggers Centennial Puzzle
    virtual void takeDamage(int amount);

    // returns flat retaliation damage from Bronze Scales (3 per relic)
    int getBronzeScalesDamage() const;

    static const int DEFAULT_DRAW = 5;

protected:
    int maxEnergy_;
    int currentEnergy_;
    Deck deck_;
    int gold_;
    std::vector<Relic*> relics_;
    bool puzzleTriggered_;   // centennial puzzle: only fires once per combat
    bool redSkullActive_;    // red skull: tracks whether the +3 str bonus is applied
};

#endif
