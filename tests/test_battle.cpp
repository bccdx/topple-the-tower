// tests/test_battle.cpp
#include "Battle.h"
#include "Card.h"
#include "Defend.h"
#include "Hero.h"
#include "Ironknight.h"
#include "Strike.h"
#include "TowerGuard.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// find first card in hand matching `name`, or -1 if it wasn't drawn this turn
int indexOf(const Hero& hero, const std::string& name) {
    const std::vector<Card*>& hand = hero.getDeck().getHand();
    for (int i = 0; i < (int)hand.size(); i++) {
        if (hand[i]->getName() == name) return i;
    }
    return -1;
}

void test_battle_initial_state() {
    Ironknight hero;
    Battle b(hero, new TowerGuard());
    b.start();

    assert(b.getState() == BATTLE_ONGOING);
    assert(b.getTurnNumber() == 1);
    // Ironknight should have drawn the default hand size
    assert(hero.getDeck().handSize() == Hero::DEFAULT_DRAW);
    assert(hero.getCurrentEnergy() == Ironknight::STARTING_ENERGY);
    // Tower Guard pre-loads an attack intent
    assert(b.getEnemy().getIntent().type == INTENT_ATTACK);
    std::cout << "PASSED: test_battle_initial_state\n";
}

void test_play_strike_damages_enemy() {
    Ironknight hero;
    Battle b(hero, new TowerGuard());
    b.start();

    int hpBefore = b.getEnemy().getCurrentHp();
    int idx = indexOf(hero, "Strike");
    if (idx < 0) {
        // 5 Strikes + 4 Defends + 1 Bash, so drawing 5 should always pull at least one Strike or Bash. skip if not
        std::cout << "SKIPPED: test_play_strike_damages_enemy (no Strike drawn)\n";
        return;
    }
    PlayResult r = b.playCardFromHand(idx);
    assert(r.success);
    assert(b.getEnemy().getCurrentHp() == hpBefore - Strike::DAMAGE);
    std::cout << "PASSED: test_play_strike_damages_enemy\n";
}

void test_cannot_play_without_energy() {
    Ironknight hero;
    Battle b(hero, new TowerGuard());
    b.start();

    // drain Energy so any non-zero-cost play must fail
    hero.spendEnergy(hero.getCurrentEnergy());
    assert(hero.getCurrentEnergy() == 0);

    PlayResult r = b.playCardFromHand(0);
    assert(!r.success);
    assert(r.message == "Not enough energy.");
    std::cout << "PASSED: test_cannot_play_without_energy\n";
}

void test_invalid_index_rejected() {
    Ironknight hero;
    Battle b(hero, new TowerGuard());
    b.start();

    PlayResult r = b.playCardFromHand(99);
    assert(!r.success);
    assert(r.message == "No card at that position.");
    std::cout << "PASSED: test_invalid_index_rejected\n";
}

void test_end_turn_runs_enemy_attack() {
    Ironknight hero;
    Battle b(hero, new TowerGuard());
    b.start();

    int hpBefore = hero.getCurrentHp();
    b.endHeroTurn();
    // Tower Guard's first intent is ATTACK 12 and we played no Block, so it should land
    assert(hero.getCurrentHp() == hpBefore - TowerGuard::ATTACK_DAMAGE);
    assert(b.getTurnNumber() == 2);
    // after the enemy turn the intent should flip to DEFEND
    assert(b.getEnemy().getIntent().type == INTENT_DEFEND);
    std::cout << "PASSED: test_end_turn_runs_enemy_attack\n";
}

void test_defend_blocks_enemy_attack() {
    Ironknight hero;
    Battle b(hero, new TowerGuard());
    b.start();

    int idx = indexOf(hero, "Defend");
    if (idx < 0) {
        std::cout << "SKIPPED: test_defend_blocks_enemy_attack (no Defend drawn)\n";
        return;
    }
    PlayResult r = b.playCardFromHand(idx);
    assert(r.success);
    assert(hero.getBlock() == Defend::BLOCK);

    int hpBefore = hero.getCurrentHp();
    b.endHeroTurn();
    // enemy hits for 12, Defend gave 5 Block, so 7 damage lands on HP
    int expected = hpBefore - (TowerGuard::ATTACK_DAMAGE - Defend::BLOCK);
    assert(hero.getCurrentHp() == expected);
    std::cout << "PASSED: test_defend_blocks_enemy_attack\n";
}

int main() {
    srand(42);
    std::cout << "Running Battle tests...\n\n";
    test_battle_initial_state();
    test_play_strike_damages_enemy();
    test_cannot_play_without_energy();
    test_invalid_index_rejected();
    test_end_turn_runs_enemy_attack();
    test_defend_blocks_enemy_attack();
    std::cout << "\nAll Battle tests passed!\n";
    return 0;
}
