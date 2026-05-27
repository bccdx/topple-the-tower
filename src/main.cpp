// src/main.cpp
// terminal UI for a run through the tower. renders state and turns keystrokes into
// Battle/Reward calls. all gameplay logic lives elsewhere so a future GUI only replaces this file

#include "Assassin.h"
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
#include <unistd.h>
#include <vector>

void clearScreen() {
    // ANSI clear + cursor home. works in most terminals
    std::cout << "\033[2J\033[H";
}

// ---- sprites ---------------------------------------------------------------
// 5 lines each. hero faces right, enemies face left

static const char* SKULL[7] = {
    "    _____   ",
    "   /     \\  ",
    "  / X   X \\ ",
    " |    ^    |",
    " |  -----  |",
    "  \\_______/ ",
    "   ||| |||  "
};

static const char* HAPPY_FACE[5] = {
    "  \\(^o^)/  ",
    "   (   )   ",
    "    \\ /   ",
    "           ",
    "           "
};

static const char* HERO_NEUTRAL[5] = {
    "  [O]       ",
    "  ]|[       ",
    "   |        ",
    "  / \\      ",
    "            "
};
static const char* HERO_ATTACK[5] = {
    "  [O]       ",
    "  ]======>  ",
    "   |        ",
    "  / \\      ",
    "            "
};
static const char* HERO_DEFEND[5] = {
    "  [O]       ",
    "  ]|[]      ",
    "   |        ",
    "  / \\      ",
    "            "
};
static const char* HERO_SKILL[5] = {
    "  \\O/      ",
    "  -|-       ",
    "   |        ",
    "  / \\      ",
    "            "
};

// assassin sprites — lighter, agile look
static const char* ASSASSIN_NEUTRAL[5] = {
    "   oO       ",
    "   /|       ",
    "   |\\      ",
    "  /         ",
    "            "
};
static const char* ASSASSIN_ATTACK[5] = {
    "   oO       ",
    "  /|-->     ",
    "  /         ",
    " /          ",
    "            "
};
static const char* ASSASSIN_DEFEND[5] = {
    "  oO.       ",
    "  \\|/      ",
    "  /|        ",
    " /          ",
    "            "
};
static const char* ASSASSIN_SKILL[5] = {
    "  *O*       ",
    "  /|\\      ",
    "   |        ",
    "  / \\      ",
    "            "
};

enum HeroAnim { HERO_ANIM_NONE, HERO_ANIM_ATTACK, HERO_ANIM_DEFEND, HERO_ANIM_SKILL };

static const char* BASIC_NEUTRAL[5] = {
    "   o   ",
    "  \\|/ ",
    "   |   ",
    "  / \\ ",
    "       "
};
static const char* BASIC_ATTACK[5] = {
    "   o   ",
    " <-|/  ",
    "   |   ",
    "  / \\ ",
    "       "
};

static const char* ELITE_NEUTRAL[5] = {
    "  [O]  ",
    "  [|]  ",
    "   |   ",
    "  /=\\ ",
    "       "
};
static const char* ELITE_ATTACK[5] = {
    "  [O]  ",
    "<=[|]  ",
    "   |   ",
    "  /=\\ ",
    "       "
};

static const char* BOSS_NEUTRAL[5] = {
    "   {O}   ",
    "  =[|]=  ",
    "    |    ",
    "  /===\\ ",
    "         "
};
static const char* BOSS_ATTACK[5] = {
    "   {O}   ",
    " <=[|]=  ",
    "    |    ",
    "  /===\\ ",
    "         "
};

static bool parsePositiveInt(const std::string& s, int& out) {
    if (s.empty()) return false;
    out = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] < '0' || s[i] > '9') return false;
        out = out * 10 + (s[i] - '0');
        if (out > 100) { out = 100; break; }
    }
    return true;
}

static std::string padRight(const std::string& s, int width) {
    if ((int)s.size() >= width) return s;
    return s + std::string(width - (int)s.size(), ' ');
}

static const char** getHeroSprite(const Hero& h, HeroAnim anim) {
    bool isAssassin = (h.getHeroType() == HERO_ASSASSIN);
    if (isAssassin) {
        switch (anim) {
            case HERO_ANIM_ATTACK: return ASSASSIN_ATTACK;
            case HERO_ANIM_DEFEND: return ASSASSIN_DEFEND;
            case HERO_ANIM_SKILL:  return ASSASSIN_SKILL;
            default:               return ASSASSIN_NEUTRAL;
        }
    }
    switch (anim) {
        case HERO_ANIM_ATTACK: return HERO_ATTACK;
        case HERO_ANIM_DEFEND: return HERO_DEFEND;
        case HERO_ANIM_SKILL:  return HERO_SKILL;
        default:               return HERO_NEUTRAL;
    }
}

static const char** getEnemyNeutralSprite(const Enemy& e) {
    switch (e.getTier()) {
        case TIER_ELITE: return ELITE_NEUTRAL;
        case TIER_BOSS:  return BOSS_NEUTRAL;
        default:         return BASIC_NEUTRAL;
    }
}

static const char** getEnemyAttackSprite(const Enemy& e) {
    switch (e.getTier()) {
        case TIER_ELITE: return ELITE_ATTACK;
        case TIER_BOSS:  return BOSS_ATTACK;
        default:         return BASIC_ATTACK;
    }
}

static void printScene(const Battle& b, HeroAnim heroAnim, bool enemyAtk) {
    const int COL = 22;
    const char** heroSpr = getHeroSprite(b.getHero(), heroAnim);
    const char** enemySpr = enemyAtk ? getEnemyAttackSprite(b.getEnemy())
                                     : getEnemyNeutralSprite(b.getEnemy());
    std::cout << padRight("  " + b.getHero().getName(), COL) << b.getEnemy().getName() << "\n";
    for (int i = 0; i < 5; i++) {
        std::cout << padRight(heroSpr[i], COL) << enemySpr[i] << "\n";
    }
    std::cout << "\n";
}

// ---- battle display --------------------------------------------------------

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

void printBattle(const Battle& b, int floor, int totalFloors,
                 HeroAnim heroAnim = HERO_ANIM_NONE, bool enemyAtk = false) {
    clearScreen();
    std::cout << "==============================================\n";
    std::cout << " Topple the Tower    Floor " << floor << "/" << totalFloors
              << "    Turn " << b.getTurnNumber() << "\n";
    std::cout << "==============================================\n\n";
    printScene(b, heroAnim, enemyAtk);
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
    reward.generateOptions(3, hero);
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

        int idx = 0;
        if (!parsePositiveInt(input, idx)) { std::cout << "Enter a number.\n"; continue; }
        if (idx == 0) { std::cout << "Skipped.\n"; return true; }
        if (idx < 1 || idx > reward.optionCount()) { std::cout << "Invalid choice.\n"; continue; }

        std::string cardName = reward.getOptions()[idx - 1]->getName();
        reward.pickCard(idx - 1, hero);
        std::cout << "Added " << cardName << " to your deck.\n";
        return true;
    }
}

// hero selection screen. returns a heap-allocated Hero* the caller owns
static Hero* selectHero() {
    clearScreen();
    std::cout << "==============================================\n";
    std::cout << " Topple the Tower\n";
    std::cout << "==============================================\n\n";
    std::cout << "Choose your hero:\n\n";
    const int COL = 20;
    std::cout << padRight("  1) Ironknight", COL) << "  2) Assassin\n";
    for (int i = 0; i < 5; i++) {
        std::cout << padRight(HERO_NEUTRAL[i], COL) << "  " << ASSASSIN_NEUTRAL[i] << "\n";
    }
    std::cout << "\n";
    std::cout << padRight("  80 HP", COL) << "  70 HP\n";
    std::cout << padRight("  armored warrior", COL) << "  quick and precise\n";
    std::cout << padRight("  heals after fights", COL) << "  draws 2 extra cards\n\n";

    std::string input;
    while (true) {
        std::cout << "Enter 1 or 2 > ";
        if (!std::getline(std::cin, input)) return NULL;
        if (input == "1") return new Ironknight();
        if (input == "2") return new Assassin();
        std::cout << "Enter 1 or 2.\n";
    }
}

int main() {
    srand((unsigned int)time(0));

    Hero* hero = selectHero();
    if (hero == NULL) return 0;

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
        Battle battle(*hero, enemy);
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
            if (!std::getline(std::cin, input)) { delete hero; return 0; }
            if (input == "") continue;

            if (input == "e" || input == "E") {
                printBattle(battle, floor + 1, map.roomCount(), HERO_ANIM_NONE, true);
                usleep(220000);
                battle.endHeroTurn();
                continue;
            }

            int idx = 0;
            if (!parsePositiveInt(input, idx)) {
                flash = "Unrecognized input. Type a card number or 'e'.";
            } else {
                // peek at card type before playing to pick the right animation
                HeroAnim anim = HERO_ANIM_ATTACK;
                const std::vector<Card*>& hand = battle.getHero().getDeck().getHand();
                if (idx >= 1 && idx - 1 < (int)hand.size()) {
                    CardType ct = hand[idx - 1]->getType();
                    if (ct == CARD_SKILL)  anim = HERO_ANIM_DEFEND;
                    if (ct == CARD_POWER)  anim = HERO_ANIM_SKILL;
                }
                PlayResult result = battle.playCardFromHand(idx - 1);
                if (!result.success) {
                    flash = result.message;
                } else {
                    printBattle(battle, floor + 1, map.roomCount(), anim, false);
                    usleep(220000);
                }
            }
        }

        printBattle(battle, floor + 1, map.roomCount());

        clearScreen();
        if (battle.getState() == BATTLE_HERO_LOST) {
            for (int i = 0; i < 7; i++) std::cout << SKULL[i] << "\n";
            std::cout << "\n  GAME OVER\n\n";
            std::cout << "*** Defeat. The tower stands. ***\n";
            delete hero;
            return 0;
        }

        // hero won this floor
        for (int i = 0; i < 5; i++) std::cout << HAPPY_FACE[i] << "\n";
        std::cout << "\n*** Floor " << (floor + 1) << " cleared! ***\n\n";

        int hpBefore = hero->getCurrentHp();
        hero->onCombatEnd();
        int healed = hero->getCurrentHp() - hpBefore;
        if (healed > 0) {
            std::cout << "Healed " << healed << " HP. ";
        }
        std::cout << "(" << hero->getCurrentHp() << "/" << hero->getMaxHp() << ")\n\n";

        Reward reward;
        reward.setGold(20 + floor * 5);
        std::cout << "You earned " << reward.getGold() << " gold.\n";
        hero->earnGold(reward.getGold());

        int relicsBefore = (int)hero->getRelics().size();
        reward.awardRelic(*hero);
        if ((int)hero->getRelics().size() > relicsBefore) {
            const Relic& r = *hero->getRelics().back();
            std::cout << "You found " << r.getName() << ": " << r.getDescription() << "\n\n";
        }

        if (!doCardReward(reward, *hero)) { delete hero; return 0; }

        if (floor < map.roomCount() - 1) {
            hero->getDeck().resetForCombat();
            std::cout << "\nPress Enter to continue to the next floor...";
            if (!std::getline(std::cin, input)) { delete hero; return 0; }
        }
    }

    clearScreen();
    for (int i = 0; i < 5; i++) std::cout << HAPPY_FACE[i] << "\n";
    std::cout << "\n*** You've toppled the tower! ***\n";
    delete hero;
    return 0;
}
