// tests/test_reward.cpp
#include "Ironknight.h"
#include "Reward.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

// written by hand before asking AI for help
void test_reward_normal() {
    Ironknight hero;
    int before = hero.getDeck().drawPileSize();

    Reward reward;
    reward.generateOptions(3);
    assert(reward.optionCount() == 3);

    bool ok = reward.pickCard(1, hero);
    assert(ok);
    assert(hero.getDeck().drawPileSize() == before + 1);
    std::cout << "PASSED: test_reward_normal\n";
}

void test_reward_skip() {
    Ironknight hero;
    int before = hero.getDeck().drawPileSize();

    Reward reward;
    reward.generateOptions(3);

    assert(!reward.pickCard(99, hero));
    assert(hero.getDeck().drawPileSize() == before);

    assert(!reward.pickCard(-1, hero));
    assert(hero.getDeck().drawPileSize() == before);
    std::cout << "PASSED: test_reward_skip\n";
}

void test_reward_boundary() {
    // pick index 0 (first option)
    {
        Ironknight hero;
        int before = hero.getDeck().drawPileSize();
        Reward reward;
        reward.generateOptions(3);
        assert(reward.pickCard(0, hero));
        assert(hero.getDeck().drawPileSize() == before + 1);
    }
    // pick index optionCount - 1 (last option)
    {
        Ironknight hero;
        int before = hero.getDeck().drawPileSize();
        Reward reward;
        reward.generateOptions(3);
        assert(reward.pickCard(reward.optionCount() - 1, hero));
        assert(hero.getDeck().drawPileSize() == before + 1);
    }
    std::cout << "PASSED: test_reward_boundary\n";
}

int main() {
    srand(42);
    std::cout << "Running Reward tests...\n\n";
    test_reward_normal();
    test_reward_skip();
    test_reward_boundary();
    std::cout << "\nAll Reward tests passed!\n";
    return 0;
}
