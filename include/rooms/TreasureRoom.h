// include/rooms/TreasureRoom.h
#ifndef TREASUREROOM_H
#define TREASUREROOM_H

#include "Room.h"

// a room that gives the player a relic. not yet implemented
class TreasureRoom : public Room {
public:
    TreasureRoom(const std::string& description);
};

#endif
