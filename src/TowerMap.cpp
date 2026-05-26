#include "TowerMap.h"
#include "BattleRoom.h"

TowerMap::TowerMap() {
    BattleRoom::EnemyKind basicPool[] = {
        BattleRoom::ENEMY_SLIME,
        BattleRoom::ENEMY_LOUSE,
        BattleRoom::ENEMY_CULTIST,
        BattleRoom::ENEMY_JAW_WORM,
        BattleRoom::ENEMY_SPIKE_SLIME
    };
    BattleRoom::EnemyKind elitePool[] = {
        BattleRoom::ENEMY_BRUTE_GUARD,
        BattleRoom::ENEMY_STONE_KNIGHT,
        BattleRoom::ENEMY_GOBLIN_ARCHER,
        BattleRoom::ENEMY_TOWER_GUARD,
        BattleRoom::ENEMY_GREMLIN_NOB,
        BattleRoom::ENEMY_LAGAVULIN
    };
    BattleRoom::EnemyKind bossPool[] = {
        BattleRoom::ENEMY_CORRUPT_KNIGHT,
        BattleRoom::ENEMY_HEXAGHOST,
        BattleRoom::ENEMY_SLIME_BOSS
    };

    int basicIdx = rand() % 5;
    int eliteIdx = rand() % 6;
    int bossIdx  = rand() % 3;

    rooms_.push_back(new BattleRoom(basicPool[basicIdx], "Floor 1 -- something stirs in the dark"));
    rooms_.push_back(new BattleRoom(elitePool[eliteIdx], "Floor 2 -- a powerful guardian blocks the way"));
    rooms_.push_back(new BattleRoom(bossPool[bossIdx],   "Floor 3 -- the ruler of the tower awaits"));
}

TowerMap::~TowerMap() {
    for (int i = 0; i < (int)rooms_.size(); i++) {
        delete rooms_[i];
    }
}

const Room* TowerMap::getRoom(int index) const {
    if (index < 0 || index >= (int)rooms_.size()) return NULL;
    return rooms_[index];
}
