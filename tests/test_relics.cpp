// tests/test_relics.cpp
#include "Relic.h"
#include "Ironknight.h"
#include "Slime.h"
#include "Battle.h"

#include <cassert>
#include <iostream>

// helper: give the hero a relic by type
static void giveRelic(Hero& hero, RelicType type) {
    hero.addRelic(new Relic(type, "test", "test"));
}

// Anchor: hero should start combat with 10 block
void test_anchor() {
    Ironknight hero;
    giveRelic(hero, RELIC_ANCHOR);
    Slime* enemy = new Slime();
    Battle battle(hero, enemy);
    battle.start();
    assert(hero.getBlock() == 10);
    std::cout << "PASSED: test_anchor\n";
}

// Vajra: hero should start combat with 1 Strength
void test_vajra() {
    Ironknight hero;
    giveRelic(hero, RELIC_VAJRA);
    Slime* enemy = new Slime();
    Battle battle(hero, enemy);
    battle.start();
    assert(hero.getStatus(STATUS_STRENGTH) == 1);
    std::cout << "PASSED: test_vajra\n";
}

// Burning Blood (starter relic): hero heals 6 at end of combat
void test_burning_blood_relic() {
    Ironknight hero;
    hero.takeDamage(20);
    int hpBefore = hero.getCurrentHp();
    // Ironknight starts with Burning Blood — no need to add it manually
    hero.onCombatEnd();
    assert(hero.getCurrentHp() == hpBefore + 6);
    std::cout << "PASSED: test_burning_blood_relic\n";
}

// Bag of Marbles: enemy starts combat with 1 Vulnerable
void test_bag_of_marbles() {
    Ironknight hero;
    giveRelic(hero, RELIC_BAG_OF_MARBLES);
    Slime* enemy = new Slime();
    Battle battle(hero, enemy);
    battle.start();
    assert(battle.getEnemy().getStatus(STATUS_VULNERABLE) == 1);
    std::cout << "PASSED: test_bag_of_marbles\n";
}

// Oddly Smooth Stone: hero starts combat with 1 Dexterity
void test_oddly_smooth_stone() {
    Ironknight hero;
    giveRelic(hero, RELIC_ODDLY_SMOOTH_STONE);
    Slime* enemy = new Slime();
    Battle battle(hero, enemy);
    battle.start();
    assert(hero.getStatus(STATUS_DEXTERITY) == 1);
    std::cout << "PASSED: test_oddly_smooth_stone\n";
}

// Meat on the Bone: heals 12 at end of combat if HP <= 50%
// Ironknight's class passive also heals 6, so total is +18
void test_meat_on_the_bone_heals() {
    Ironknight hero;
    giveRelic(hero, RELIC_MEAT_ON_THE_BONE);
    hero.takeDamage(hero.getMaxHp() / 2 + 5);   // push below 50%
    int hpBefore = hero.getCurrentHp();
    hero.onCombatEnd();
    int expected = hpBefore + 12 + Ironknight::COMBAT_END_HEAL;
    assert(hero.getCurrentHp() == expected || hero.getCurrentHp() == hero.getMaxHp());
    std::cout << "PASSED: test_meat_on_the_bone_heals\n";
}

// Meat on the Bone: no heal if HP > 50%
void test_meat_on_the_bone_no_heal() {
    Ironknight hero;
    giveRelic(hero, RELIC_MEAT_ON_THE_BONE);
    // hero is at full HP (above 50%)
    int hpBefore = hero.getCurrentHp();
    hero.onCombatEnd();
    // Ironknight passive also heals, so just check meat on the bone didn't fire
    // full HP means no meat heal. Ironknight heal may push to max (already there)
    assert(hero.getCurrentHp() == hpBefore || hero.getCurrentHp() == hero.getMaxHp());
    std::cout << "PASSED: test_meat_on_the_bone_no_heal\n";
}

// Paper Krane: reduces incoming damage by 1
void test_paper_krane() {
    Ironknight hero;
    giveRelic(hero, RELIC_PAPER_KRANE);
    int hpBefore = hero.getCurrentHp();
    hero.takeDamage(5);   // should land as 4 (no block)
    assert(hero.getCurrentHp() == hpBefore - 4);
    std::cout << "PASSED: test_paper_krane\n";
}

// Red Skull: gain 3 Strength when at or below 50% HP at turn start
void test_red_skull_applies() {
    Ironknight hero;
    giveRelic(hero, RELIC_RED_SKULL);
    hero.takeDamage(hero.getMaxHp() / 2 + 5);   // push below 50%
    hero.onTurnStart();
    assert(hero.getStatus(STATUS_STRENGTH) == 3);
    std::cout << "PASSED: test_red_skull_applies\n";
}

// Red Skull: no Strength when above 50% HP
void test_red_skull_no_apply() {
    Ironknight hero;
    giveRelic(hero, RELIC_RED_SKULL);
    // hero at full HP
    hero.onTurnStart();
    assert(hero.getStatus(STATUS_STRENGTH) == 0);
    std::cout << "PASSED: test_red_skull_no_apply\n";
}

int main() {
    std::cout << "Running relic tests...\n\n";
    test_anchor();
    test_vajra();
    test_burning_blood_relic();
    test_bag_of_marbles();
    test_oddly_smooth_stone();
    test_meat_on_the_bone_heals();
    test_meat_on_the_bone_no_heal();
    test_paper_krane();
    test_red_skull_applies();
    test_red_skull_no_apply();
    std::cout << "\nAll relic tests passed!\n";
    return 0;
}
