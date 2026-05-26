// src/main.cpp
// terminal UI for a single battle. just renders state and turns keystrokes into Battle calls.
// all gameplay logic lives in Battle/Hero/Enemy/Deck/Card, so a future GUI only replaces this file

#include "Battle.h"
#include "Card.h"
#include "Character.h"
#include "Enemy.h"
#include "Hero.h"
#include "Ironknight.h"
#include "TowerGuard.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

void clearScreen() {
    // ANSI clear + cursor home. works in most terminals
    std::cout << "\033[2J\033[H";
}

void printStatuses(const Character& c) {
    bool first = true;
    for (int i = 0; i < STATUS_COUNT; i++) {
        StatusType s = (StatusType)i;
        if (c.getStatus(s) > 0) {
            if (!first) std::cout << ", ";
            std::cout << statusToString(s) << " " << c.getStatus(s);
            first = false;
        }
    }
    if (first) std::cout << "(none)";
}

void printEnemy(const Enemy& e) {
    std::cout << "== Enemy ==\n";
    std::cout << "  " << e.getName()
              << "    HP " << e.getCurrentHp() << "/" << e.getMaxHp()
              << "    Block " << e.getBlock() << "\n";
    std::cout << "  Statuses: ";
    printStatuses(e);
    std::cout << "\n";

    const Intent& i = e.getIntent();
    std::cout << "  Intent:   " << intentTypeToString(i.type);
    if (i.type == INTENT_ATTACK) {
        std::cout << " " << i.value;
        if (i.hits > 1) std::cout << " x " << i.hits;
        std::cout << " dmg";
    } else if (i.type == INTENT_DEFEND) {
        std::cout << " +" << i.value << " block";
    }
    if (i.description != "") std::cout << "  (" << i.description << ")";
    std::cout << "\n";
}

void printHero(const Hero& h) {
    std::cout << "== " << h.getName() << " ==\n";
    std::cout << "  HP " << h.getCurrentHp() << "/" << h.getMaxHp()
              << "    Block " << h.getBlock()
              << "    Energy " << h.getCurrentEnergy() << "/" << h.getMaxEnergy()
              << "\n";
    std::cout << "  Statuses: ";
    printStatuses(h);
    std::cout << "\n";
    std::cout << "  Draw " << h.getDeck().drawPileSize()
              << "  |  Discard " << h.getDeck().discardPileSize()
              << "  |  Exhaust " << h.getDeck().exhaustPileSize()
              << "\n";
}

void printPlayedThisTurn(const Battle& b) {
    const std::vector<std::string>& played = b.getCardsPlayedThisTurn();
    std::cout << "== Played this turn ==\n";
    if (played.size() == 0) {
        std::cout << "  (none yet)\n";
        return;
    }
    std::cout << "  ";
    for (int i = 0; i < (int)played.size(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << (i + 1) << ") " << played[i];
    }
    std::cout << "\n";
}

void printHand(const Hero& h) {
    const std::vector<Card*>& hand = h.getDeck().getHand();
    std::cout << "== Hand ==\n";
    if (hand.size() == 0) {
        std::cout << "  (empty)\n";
        return;
    }
    for (int i = 0; i < (int)hand.size(); i++) {
        const Card& c = *hand[i];
        std::cout << "  " << (i + 1) << ") [" << c.getCost() << "] "
                  << c.getName() << " - " << c.getDescription() << "\n";
    }
}

void printBattle(const Battle& b) {
    clearScreen();
    std::cout << "==============================================\n";
    std::cout << " Topple the Tower    Turn " << b.getTurnNumber() << "\n";
    std::cout << "==============================================\n\n";
    printEnemy(b.getEnemy());
    std::cout << "\n";
    printHero(b.getHero());
    std::cout << "\n";
    printPlayedThisTurn(b);
    std::cout << "\n";
    printHand(b.getHero());
    std::cout << "\n";
}

int main() {
    // seed the random number generator once for the whole program
    srand((unsigned int)time(0));

    Ironknight hero;
    Battle battle(hero, new TowerGuard());
    battle.start();

    std::string flash;
    std::string input;

    while (battle.getState() == BATTLE_ONGOING) {
        printBattle(battle);
        if (flash != "") {
            std::cout << ">> " << flash << "\n\n";
            flash = "";
        }
        std::cout << "Enter card # to play, or 'e' to end turn > ";
        if (!std::getline(std::cin, input)) break;
        if (input == "") continue;

        if (input == "e" || input == "E") {
            battle.endHeroTurn();
            continue;
        }

        // parse the input as a positive integer (digits only)
        bool isNumber = true;
        int idx = 0;
        for (int i = 0; i < (int)input.size(); i++) {
            if (input[i] < '0' || input[i] > '9') {
                isNumber = false;
                break;
            }
            idx = idx * 10 + (input[i] - '0');
        }

        if (!isNumber) {
            flash = "Unrecognized input. Type a card number or 'e'.";
        } else {
            PlayResult result = battle.playCardFromHand(idx - 1);
            if (!result.success) flash = result.message;
        }
    }

    printBattle(battle);
    if (battle.getState() == BATTLE_HERO_WON) {
        std::cout << "*** Victory! The tower trembles. ***\n";
    } else {
        std::cout << "*** Defeat. The tower stands. ***\n";
    }
    return 0;
}
