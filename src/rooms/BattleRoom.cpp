#include "BattleRoom.h"

#include "Slime.h"
#include "Louse.h"
#include "Cultist.h"
#include "JawWorm.h"
#include "SpikeSlime.h"
#include "BruteGuard.h"
#include "StoneKnight.h"
#include "GoblinArcher.h"
#include "TowerGuard.h"
#include "GremlinNob.h"
#include "Lagavulin.h"
#include "CorruptKnight.h"
#include "Hexaghost.h"
#include "SlimeBoss.h"

BattleRoom::BattleRoom(EnemyKind kind, const std::string& description)
    : Room(ROOM_BATTLE, description) {
    kind_ = kind;
}

Enemy* BattleRoom::createEnemy() const {
    switch (kind_) {
        case ENEMY_SLIME:          return new Slime();
        case ENEMY_LOUSE:          return new Louse();
        case ENEMY_CULTIST:        return new Cultist();
        case ENEMY_JAW_WORM:       return new JawWorm();
        case ENEMY_SPIKE_SLIME:    return new SpikeSlime();
        case ENEMY_BRUTE_GUARD:    return new BruteGuard();
        case ENEMY_STONE_KNIGHT:   return new StoneKnight();
        case ENEMY_GOBLIN_ARCHER:  return new GoblinArcher();
        case ENEMY_TOWER_GUARD:    return new TowerGuard();
        case ENEMY_GREMLIN_NOB:    return new GremlinNob();
        case ENEMY_LAGAVULIN:      return new Lagavulin();
        case ENEMY_CORRUPT_KNIGHT: return new CorruptKnight();
        case ENEMY_HEXAGHOST:      return new Hexaghost();
        case ENEMY_SLIME_BOSS:     return new SlimeBoss();
    }
    return new CorruptKnight();
}
