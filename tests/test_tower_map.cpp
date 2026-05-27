// tests/test_tower_map.cpp
#include "TowerMap.h"
#include "BattleRoom.h"
#include "Enemy.h"
#include "Ironknight.h"
#include "Deck.h"
#include "Strike.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

// map has exactly 3 rooms and all are battle rooms
void test_map_structure() {
    srand(42);
    TowerMap map;
    assert(map.roomCount() == 3);
    for (int i = 0; i < map.roomCount(); i++) {
        const Room* r = map.getRoom(i);
        assert(r != NULL);
        assert(r->getType() == ROOM_BATTLE);
    }
    std::cout << "PASSED: test_map_structure\n";
}

// out-of-bounds index returns NULL
void test_map_bounds() {
    srand(42);
    TowerMap map;
    assert(map.getRoom(-1) == NULL);
    assert(map.getRoom(map.roomCount()) == NULL);
    std::cout << "PASSED: test_map_bounds\n";
}

// each battle room creates a non-null enemy with the right tier
void test_battle_room_tiers() {
    srand(42);
    TowerMap map;

    // floor 0 is basic, floor 1 is elite, floor 2 is boss
    Enemy* basic = map.getRoom(0)->createEnemy();
    assert(basic != NULL);
    assert(basic->getTier() == TIER_BASIC);
    delete basic;

    Enemy* elite = map.getRoom(1)->createEnemy();
    assert(elite != NULL);
    assert(elite->getTier() == TIER_ELITE);
    delete elite;

    Enemy* boss = map.getRoom(2)->createEnemy();
    assert(boss != NULL);
    assert(boss->getTier() == TIER_BOSS);
    delete boss;

    std::cout << "PASSED: test_battle_room_tiers\n";
}

// resetForCombat moves hand and discard back to draw pile. exhaust stays out
void test_deck_reset_for_combat() {
    Deck deck;
    deck.addCard(new Strike());
    deck.addCard(new Strike());
    deck.addCard(new Strike());
    deck.shuffleDrawPile();
    deck.draw(2);

    assert(deck.handSize() == 2);
    assert(deck.drawPileSize() == 1);

    deck.resetForCombat();

    assert(deck.handSize() == 0);
    assert(deck.discardPileSize() == 0);
    assert(deck.drawPileSize() == 3);
    std::cout << "PASSED: test_deck_reset_for_combat\n";
}

// exhaust pile stays out after resetForCombat
void test_deck_reset_exhaust_stays() {
    Deck deck;
    deck.addCard(new Strike());
    deck.addCard(new Strike());
    deck.shuffleDrawPile();
    deck.draw(2);
    // exhaust one card from hand
    deck.exhaust(deck.takeFromHand(0));

    assert(deck.exhaustPileSize() == 1);
    deck.resetForCombat();

    assert(deck.exhaustPileSize() == 1);
    assert(deck.drawPileSize() == 1);
    std::cout << "PASSED: test_deck_reset_exhaust_stays\n";
}

// onCombatEnd heals 6 HP and does not overheal
void test_ironknight_combat_end_heal() {
    Ironknight hero;
    hero.takeDamage(20);
    int hpBefore = hero.getCurrentHp();
    hero.onCombatEnd();
    assert(hero.getCurrentHp() == hpBefore + Ironknight::COMBAT_END_HEAL);
    std::cout << "PASSED: test_ironknight_combat_end_heal\n";
}

void test_ironknight_combat_end_no_overheal() {
    Ironknight hero;
    // hero is at full HP
    assert(hero.getCurrentHp() == hero.getMaxHp());
    hero.onCombatEnd();
    assert(hero.getCurrentHp() == hero.getMaxHp());
    std::cout << "PASSED: test_ironknight_combat_end_no_overheal\n";
}

int main() {
    srand(42);
    std::cout << "Running TowerMap tests...\n\n";
    test_map_structure();
    test_map_bounds();
    test_battle_room_tiers();
    test_deck_reset_for_combat();
    test_deck_reset_exhaust_stays();
    test_ironknight_combat_end_heal();
    test_ironknight_combat_end_no_overheal();
    std::cout << "\nAll TowerMap tests passed!\n";
    return 0;
}
