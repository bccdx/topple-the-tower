#include "Battle.h"

#include "Card.h"
#include "Hero.h"

Battle::Battle(Hero& hero, Enemy* enemy) : hero_(hero) {
    enemy_ = enemy;
    state_ = BATTLE_ONGOING;
    turnNumber_ = 0;
}

Battle::~Battle() {
    delete enemy_;
}

void Battle::start() {
    turnNumber_ = 1;
    startHeroTurn();
}

void Battle::startHeroTurn() {
    cardsPlayedThisTurn_.clear();
    hero_.onTurnStart();
    refreshState();
}

PlayResult Battle::playCardFromHand(int handIndex) {
    PlayResult result;
    if (state_ != BATTLE_ONGOING) {
        result.success = false;
        result.message = "Battle is over.";
        return result;
    }
    Deck& deck = hero_.getDeck();
    if (handIndex < 0 || handIndex >= deck.handSize()) {
        result.success = false;
        result.message = "No card at that position.";
        return result;
    }
    Card* preview = deck.getHand()[handIndex];
    if (preview->getCost() > hero_.getCurrentEnergy()) {
        result.success = false;
        result.message = "Not enough energy.";
        return result;
    }

    // take the card out of the hand before resolving so play() sees a clean hand state
    Card* played = deck.takeFromHand(handIndex);
    hero_.spendEnergy(played->getCost());

    Character* target;
    if (played->getTargetType() == TARGET_ENEMY) {
        target = enemy_;
    } else {
        target = &hero_;
    }
    cardsPlayedThisTurn_.push_back(played->getName());
    played->play(hero_, *target, *this);

    deck.discard(played);
    refreshState();
    result.success = true;
    result.message = "";
    return result;
}

void Battle::endHeroTurn() {
    if (state_ != BATTLE_ONGOING) return;

    hero_.onTurnEnd();
    refreshState();
    if (state_ != BATTLE_ONGOING) return;

    runEnemyTurn();
    if (state_ != BATTLE_ONGOING) return;

    turnNumber_ += 1;
    startHeroTurn();
}

void Battle::runEnemyTurn() {
    enemy_->onTurnStart();
    enemy_->takeTurn(hero_, *this);
    refreshState();
    if (state_ != BATTLE_ONGOING) return;
    enemy_->onTurnEnd();
    enemy_->chooseNextIntent();
}

void Battle::refreshState() {
    if (!hero_.isAlive()) {
        state_ = BATTLE_HERO_LOST;
    } else if (!enemy_->isAlive()) {
        state_ = BATTLE_HERO_WON;
    }
}
