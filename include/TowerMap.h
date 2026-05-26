// include/TowerMap.h
#ifndef TOWERMAP_H
#define TOWERMAP_H

#include "Room.h"
#include <vector>

// the fixed path of rooms the player climbs through
class TowerMap {
public:
    TowerMap();
    ~TowerMap();
    int roomCount() const { return (int)rooms_.size(); }
    const Room* getRoom(int index) const;
private:
    std::vector<Room*> rooms_;
};

#endif
