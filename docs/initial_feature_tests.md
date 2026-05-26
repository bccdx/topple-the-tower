# Initial Feature Test Cases

## Feature: Single Battle

The first implemented feature is a complete, runnable single battle. An Ironknight hero with a starter deck of 5 Strike + 4 Defend + 1 Bash fights a Tower Guard enemy in turn-based combat. The tests below verify the core combat flow, the Energy and Block rules, and the status system.

### Test 1: Normal Operation
- **What it tests:** Battle starts with the hero drawing the default 5-card hand, Energy reset to the Ironknight maximum (3), and the Tower Guard pre-loading an attack intent for the first turn.
- **Where:** `tests/test_battle.cpp` — `test_battle_initial_state`
- **Expected result:** `hand size == 5`, `Energy == 3`, `intent.type == ATTACK`.
- **Result:** Pass

### Test 2: Edge Case
- **What it tests:** Trying to play a card with not enough Energy fails cleanly without mutating game state.
- **Where:** `tests/test_battle.cpp` — `test_cannot_play_without_energy`
- **Expected result:** `playCardFromHand` returns `{success=false, message="Not enough energy."}` after Energy has been drained to 0.
- **Result:** Pass

### Test 3: Boundary Condition
- **What it tests:** Block exactly mitigates an enemy attack. Tower Guard hits for 12, Defend gives 5 Block, so 7 damage lands on HP.
- **Where:** `tests/test_battle.cpp` — `test_defend_blocks_enemy_attack`
- **Expected result:** Hero HP decreases by exactly `ATTACK_DAMAGE - BLOCK = 12 - 5 = 7`.
- **Result:** Pass

### Additional Coverage
Beyond the three required cases, the suite also covers:
- Damage math under Weak, Vulnerable, and Strength modifiers (`tests/test_character.cpp`)
- Frail's 25% reduction on Block gain
- Artifact absorbing exactly one debuff application regardless of stack size
- Deck reshuffle when the draw pile empties and the discard pile is not (`tests/test_deck.cpp`)
- Turn-based status decay (Weak, Frail, Vulnerable tick down each turn while Strength and Dexterity persist)
- Lethal damage flooring HP at 0 (`tests/test_character.cpp`)
- Invalid hand index rejected with a sensible error message (`tests/test_battle.cpp`)

All four test executables are registered with CTest in `CMakeLists.txt`: `CounterTests`, `CharacterTests`, `DeckTests`, `BattleTests`.

### CTest Output

```
$ ctest --test-dir build --verbose
UpdateCTestConfiguration  from :/Users/dannaxu/Desktop/topple-the-tower/build/DartConfiguration.tcl
Test project /Users/dannaxu/Desktop/topple-the-tower/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: CounterTests

1: Test command: /Users/dannaxu/Desktop/topple-the-tower/build/test_counter
1: Working Directory: /Users/dannaxu/Desktop/topple-the-tower/build
1: Test timeout computed to be: 10000000
1: Running Counter tests...
1:
1: PASSED: test_initial_value
1: PASSED: test_increment
1: PASSED: test_decrement
1: PASSED: test_reset
1:
1: All tests passed!
1/4 Test #1: CounterTests .....................   Passed    0.26 sec
test 2
    Start 2: CharacterTests

2: Test command: /Users/dannaxu/Desktop/topple-the-tower/build/test_character
2: Working Directory: /Users/dannaxu/Desktop/topple-the-tower/build
2: Test timeout computed to be: 10000000
2: Running Character tests...
2:
2: PASSED: test_initial_state
2: PASSED: test_take_damage_with_block
2: PASSED: test_take_damage_lethal_floors_at_zero
2: PASSED: test_vulnerable_amplifies_attack
2: PASSED: test_weak_reduces_attack
2: PASSED: test_strength_adds_to_attack
2: PASSED: test_frail_reduces_block
2: PASSED: test_artifact_absorbs_debuff
2: PASSED: test_turn_end_ticks_debuffs
2: PASSED: test_turn_start_clears_block
2:
2: All Character tests passed!
2/4 Test #2: CharacterTests ...................   Passed    0.10 sec
test 3
    Start 3: DeckTests

3: Test command: /Users/dannaxu/Desktop/topple-the-tower/build/test_deck
3: Working Directory: /Users/dannaxu/Desktop/topple-the-tower/build
3: Test timeout computed to be: 10000000
3: Running Deck tests...
3:
3: PASSED: test_add_and_draw
3: PASSED: test_draw_more_than_available_with_empty_discard
3: PASSED: test_reshuffle_discard_into_draw
3: PASSED: test_take_from_hand_moves_ownership
3: PASSED: test_discard_returns_card_to_discard_pile
3:
3: All Deck tests passed!
3/4 Test #3: DeckTests ........................   Passed    0.11 sec
test 4
    Start 4: BattleTests

4: Test command: /Users/dannaxu/Desktop/topple-the-tower/build/test_battle
4: Working Directory: /Users/dannaxu/Desktop/topple-the-tower/build
4: Test timeout computed to be: 10000000
4: Running Battle tests...
4:
4: PASSED: test_battle_initial_state
4: PASSED: test_play_strike_damages_enemy
4: PASSED: test_cannot_play_without_energy
4: PASSED: test_invalid_index_rejected
4: PASSED: test_end_turn_runs_enemy_attack
4: PASSED: test_defend_blocks_enemy_attack
4:
4: All Battle tests passed!
4/4 Test #4: BattleTests ......................   Passed    0.17 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =   0.65 sec
```
