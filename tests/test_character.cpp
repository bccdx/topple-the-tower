// tests/test_character.cpp
#include "Character.h"

#include <cassert>
#include <iostream>

// concrete instantiation so we can test the abstract base directly
class TestCharacter : public Character {
public:
    TestCharacter(const std::string& name, int hp) : Character(name, hp) {}
};

void test_initial_state() {
    TestCharacter c("Tester", 50);
    assert(c.getCurrentHp() == 50);
    assert(c.getMaxHp() == 50);
    assert(c.getBlock() == 0);
    assert(c.isAlive());
    assert(c.getStatus(STATUS_WEAK) == 0);
    std::cout << "PASSED: test_initial_state\n";
}

void test_take_damage_with_block() {
    TestCharacter c("Tester", 50);
    c.gainBlock(10);
    c.takeDamage(7);
    assert(c.getBlock() == 3);
    assert(c.getCurrentHp() == 50);

    c.takeDamage(5);             // 3 Block absorbs, 2 leaks to HP
    assert(c.getBlock() == 0);
    assert(c.getCurrentHp() == 48);
    std::cout << "PASSED: test_take_damage_with_block\n";
}

void test_take_damage_lethal_floors_at_zero() {
    TestCharacter c("Tester", 10);
    c.takeDamage(999);
    assert(c.getCurrentHp() == 0);
    assert(!c.isAlive());
    std::cout << "PASSED: test_take_damage_lethal_floors_at_zero\n";
}

void test_vulnerable_amplifies_attack() {
    TestCharacter attacker("A", 50);
    TestCharacter victim("V", 50);
    victim.applyStatus(STATUS_VULNERABLE, 1);
    int dealt = attacker.dealAttackDamage(victim, 10);   // 10 * 1.5 = 15
    assert(dealt == 15);
    assert(victim.getCurrentHp() == 35);
    std::cout << "PASSED: test_vulnerable_amplifies_attack\n";
}

void test_weak_reduces_attack() {
    TestCharacter attacker("A", 50);
    TestCharacter victim("V", 50);
    attacker.applyStatus(STATUS_WEAK, 1);
    int dealt = attacker.dealAttackDamage(victim, 10);   // 10 * 0.75 = 7
    assert(dealt == 7);
    assert(victim.getCurrentHp() == 43);
    std::cout << "PASSED: test_weak_reduces_attack\n";
}

void test_strength_adds_to_attack() {
    TestCharacter attacker("A", 50);
    TestCharacter victim("V", 50);
    attacker.applyStatus(STATUS_STRENGTH, 3);
    int dealt = attacker.dealAttackDamage(victim, 6);    // 6 + 3 = 9
    assert(dealt == 9);
    assert(victim.getCurrentHp() == 41);
    std::cout << "PASSED: test_strength_adds_to_attack\n";
}

void test_frail_reduces_block() {
    TestCharacter c("Tester", 50);
    c.applyStatus(STATUS_FRAIL, 1);
    c.gainBlock(8);                          // 8 * 0.75 = 6
    assert(c.getBlock() == 6);
    std::cout << "PASSED: test_frail_reduces_block\n";
}

void test_artifact_absorbs_debuff() {
    TestCharacter c("Tester", 50);
    c.applyStatus(STATUS_ARTIFACT, 2);
    // first debuff application, one Artifact eats the whole thing
    c.applyStatus(STATUS_VULNERABLE, 3);
    assert(c.getStatus(STATUS_ARTIFACT) == 1);
    assert(c.getStatus(STATUS_VULNERABLE) == 0);
    // second application consumes the last Artifact
    c.applyStatus(STATUS_WEAK, 1);
    assert(c.getStatus(STATUS_ARTIFACT) == 0);
    assert(c.getStatus(STATUS_WEAK) == 0);
    // no Artifact left, debuffs land normally
    c.applyStatus(STATUS_VULNERABLE, 2);
    assert(c.getStatus(STATUS_VULNERABLE) == 2);
    std::cout << "PASSED: test_artifact_absorbs_debuff\n";
}

void test_turn_end_ticks_debuffs() {
    TestCharacter c("Tester", 50);
    c.applyStatus(STATUS_VULNERABLE, 2);
    c.applyStatus(STATUS_STRENGTH, 3);
    c.onTurnEnd();
    assert(c.getStatus(STATUS_VULNERABLE) == 1);
    assert(c.getStatus(STATUS_STRENGTH) == 3);  // permanent
    c.onTurnEnd();
    assert(c.getStatus(STATUS_VULNERABLE) == 0);
    std::cout << "PASSED: test_turn_end_ticks_debuffs\n";
}

void test_turn_start_clears_block() {
    TestCharacter c("Tester", 50);
    c.gainBlock(7);
    c.onTurnStart();
    assert(c.getBlock() == 0);
    std::cout << "PASSED: test_turn_start_clears_block\n";
}

int main() {
    std::cout << "Running Character tests...\n\n";
    test_initial_state();
    test_take_damage_with_block();
    test_take_damage_lethal_floors_at_zero();
    test_vulnerable_amplifies_attack();
    test_weak_reduces_attack();
    test_strength_adds_to_attack();
    test_frail_reduces_block();
    test_artifact_absorbs_debuff();
    test_turn_end_ticks_debuffs();
    test_turn_start_clears_block();
    std::cout << "\nAll Character tests passed!\n";
    return 0;
}
