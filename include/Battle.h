// include/Battle.h
#ifndef BATTLE_H
#define BATTLE_H

#include "Enemy.h"

#include <string>
#include <vector>

class Hero;

enum BattleState { BATTLE_ONGOING, BATTLE_HERO_WON, BATTLE_HERO_LOST };

// what happened when you tried to play a card. message has the reason if it failed
struct PlayResult {
    bool success;
    std::string message;
};

// owns the turn state for one combat. no I/O in here, so a future GUI can reuse this class
class Battle {
public:
    Battle(Hero& hero, Enemy* enemy);
    ~Battle();

    Hero& getHero()              { return hero_; }
    Enemy& getEnemy()            { return *enemy_; }
    const Hero& getHero() const  { return hero_; }
    const Enemy& getEnemy() const { return *enemy_; }

    BattleState getState() const { return state_; }
    int getTurnNumber() const    { return turnNumber_; }

    // names of cards the hero has played this turn, in play order. cleared each turn
    const std::vector<std::string>& getCardsPlayedThisTurn() const { return cardsPlayedThisTurn_; }

    // start-of-combat setup, opens turn 1
    void start();

    // try to play card #handIndex from the hand
    PlayResult playCardFromHand(int handIndex);

    // end the hero's turn. discards the hand, runs the enemy turn, opens the next hero turn (if combat continues)
    void endHeroTurn();

private:
    void startHeroTurn();
    void runEnemyTurn();
    void refreshState();

    Hero& hero_;
    Enemy* enemy_;
    BattleState state_;
    int turnNumber_;
    std::vector<std::string> cardsPlayedThisTurn_;
};

#endif
