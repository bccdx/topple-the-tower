// include/rooms/CampfireRoom.h
#ifndef CAMPFIREROOM_H
#define CAMPFIREROOM_H

#include "Room.h"

// a room where the player can rest and heal or upgrade a card. not yet implemented
class CampfireRoom : public Room {
public:
    CampfireRoom(const std::string& description);
};

#endif
