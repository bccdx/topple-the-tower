// include/rooms/BattleRoom.h
#ifndef BATTLEROOM_H
#define BATTLEROOM_H

#include "Room.h"

// a room that starts a fight when entered
class BattleRoom : public Room {
public:
    enum EnemyKind {
        // basic
        ENEMY_SLIME, ENEMY_LOUSE, ENEMY_CULTIST, ENEMY_JAW_WORM, ENEMY_SPIKE_SLIME,
        // elite
        ENEMY_BRUTE_GUARD, ENEMY_STONE_KNIGHT, ENEMY_GOBLIN_ARCHER, ENEMY_TOWER_GUARD,
        ENEMY_GREMLIN_NOB, ENEMY_LAGAVULIN,
        // boss
        ENEMY_CORRUPT_KNIGHT, ENEMY_HEXAGHOST, ENEMY_SLIME_BOSS
    };
    BattleRoom(EnemyKind kind, const std::string& description);
    virtual Enemy* createEnemy() const;
private:
    EnemyKind kind_;
};

#endif
