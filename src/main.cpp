// src/main.cpp
// terminal UI for a run through the tower. renders state and turns keystrokes into
// Battle/Reward calls. all gameplay logic lives elsewhere so a future GUI only replaces this file

#include "Battle.h"
#include "BattleRoom.h"
#include "Card.h"
#include "Character.h"
#include "Enemy.h"
#include "Hero.h"
#include "Ironknight.h"
#include "Relic.h"
#include "Reward.h"
#include "Room.h"
#include "TowerMap.h"

#include <cstdlib>
#include <ctime>
#include <iomanip>
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
              << "    HP " << std::setw(3) << e.getCurrentHp() << "/" << e.getMaxHp()
              << "    Block " << std::setw(3) << e.getBlock() << "\n";
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
    std::cout << "  HP " << std::setw(3) << h.getCurrentHp() << "/" << h.getMaxHp()
              << "    Block " << std::setw(3) << h.getBlock()
              << "    Energy " << h.getCurrentEnergy() << "/" << h.getMaxEnergy()
              << "\n";
    std::cout << "  Statuses: ";
    printStatuses(h);
    std::cout << "\n";
    std::cout << "  Draw " << std::setw(2) << h.getDeck().drawPileSize()
              << "  |  Discard " << std::setw(2) << h.getDeck().discardPileSize()
              << "  |  Exhaust " << std::setw(2) << h.getDeck().exhaustPileSize()
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
    const int HAND_SLOTS = 10;
    std::cout << "== Hand ==\n";
    for (int i = 0; i < HAND_SLOTS; i++) {
        if (i < (int)hand.size()) {
            const Card& c = *hand[i];
            std::cout << "  " << (i + 1) << ") [" << c.getCost() << "] "
                      << c.getName() << " - " << c.getDescription() << "\n";
        } else {
            std::cout << "\n";
        }
    }
}

void printBattle(const Battle& b, int floor, int totalFloors) {
    clearScreen();
    std::cout << "==============================================\n";
    std::cout << " Topple the Tower    Floor " << floor << "/" << totalFloors
              << "    Turn " << b.getTurnNumber() << "\n";
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

// run the card pick reward loop. returns false if stdin closed
bool doCardReward(Reward& reward, Hero& hero) {
    reward.generateOptions(3);
    std::cout << "== Choose a card to add to your deck ==\n";
    const std::vector<Card*>& opts = reward.getOptions();
    for (int i = 0; i < (int)opts.size(); i++) {
        const Card& c = *opts[i];
        std::cout << "  " << (i + 1) << ") [" << c.getCost() << "] "
                  << c.getName() << " - " << c.getDescription() << "\n";
    }
    std::cout << "  0) Skip\n\n";

    std::string input;
    while (true) {
        std::cout << "Enter 1-" << reward.optionCount() << " to pick, or 0 to skip > ";
        if (!std::getline(std::cin, input)) return false;
        if (input.size() == 0) { std::cout << "Enter a number.\n"; continue; }

        bool isNumber = true;
        int idx = 0;
        for (int i = 0; i < (int)input.size(); i++) {
            if (input[i] < '0' || input[i] > '9') { isNumber = false; break; }
            idx = idx * 10 + (input[i] - '0');
            if (idx > 100) { idx = 100; break; }
        }

        if (!isNumber) { std::cout << "Enter a number.\n"; continue; }
        if (idx == 0) { std::cout << "Skipped.\n"; return true; }
        if (idx < 1 || idx > reward.optionCount()) { std::cout << "Invalid choice.\n"; continue; }

        std::string cardName = reward.getOptions()[idx - 1]->getName();
        reward.pickCard(idx - 1, hero);
        std::cout << "Added " << cardName << " to your deck.\n";
        return true;
    }
}

int main() {
    srand((unsigned int)time(0));

    Ironknight hero;
    TowerMap map;

    std::string flash;
    std::string input;

    for (int floor = 0; floor < map.roomCount(); floor++) {
        const Room* room = map.getRoom(floor);

        if (room->getType() != ROOM_BATTLE) {
            // other room types aren't implemented yet
            clearScreen();
            std::cout << room->getDescription() << "\n";
            std::cout << "(this room type isn't implemented yet)\n\n";
            std::cout << "Press Enter to continue...";
            std::getline(std::cin, input);
            continue;
        }

        Enemy* enemy = room->createEnemy();
        Battle battle(hero, enemy);
        battle.start();

        while (battle.getState() == BATTLE_ONGOING) {
            printBattle(battle, floor + 1, map.roomCount());
            if (flash != "") {
                std::cout << "  >> " << flash << "\n";
                flash = "";
            } else {
                std::cout << "\n";
            }
            std::cout << "Enter card # to play, or 'e' to end turn > ";
            if (!std::getline(std::cin, input)) goto run_over;
            if (input == "") continue;

            if (input == "e" || input == "E") {
                battle.endHeroTurn();
                continue;
            }

            bool isNumber = true;
            int idx = 0;
            for (int i = 0; i < (int)input.size(); i++) {
                if (input[i] < '0' || input[i] > '9') { isNumber = false; break; }
                idx = idx * 10 + (input[i] - '0');
                if (idx > 100) { idx = 100; break; }
            }

            if (!isNumber) {
                flash = "Unrecognized input. Type a card number or 'e'.";
            } else {
                PlayResult result = battle.playCardFromHand(idx - 1);
                if (!result.success) flash = result.message;
            }
        }

        printBattle(battle, floor + 1, map.roomCount());

        clearScreen();
        if (battle.getState() == BATTLE_HERO_LOST) {
            std::cout << "*** Defeat. The tower stands. ***\n";
            return 0;
        }

        // hero won this floor
        std::cout << "*** Floor " << (floor + 1) << " cleared! ***\n\n";

        hero.onCombatEnd();
        std::cout << "Burning Blood: healed " << Ironknight::COMBAT_END_HEAL << " HP. ("
                  << hero.getCurrentHp() << "/" << hero.getMaxHp() << ")\n\n";

        Reward reward;
        reward.setGold(20 + floor * 5);
        std::cout << "You earned " << reward.getGold() << " gold.\n";
        hero.earnGold(reward.getGold());

        reward.awardRelic(hero);
        const std::vector<Relic*>& relics = hero.getRelics();
        const Relic& r = *relics.back();
        std::cout << "You found " << r.getName() << ": " << r.getDescription() << "\n\n";

        if (!doCardReward(reward, hero)) goto run_over;

        if (floor < map.roomCount() - 1) {
            hero.getDeck().resetForCombat();
            std::cout << "\nPress Enter to continue to the next floor...";
            if (!std::getline(std::cin, input)) goto run_over;
        }
    }

    clearScreen();
    std::cout << "*** You've toppled the tower! ***\n";
    return 0;

run_over:
    return 0;
}
