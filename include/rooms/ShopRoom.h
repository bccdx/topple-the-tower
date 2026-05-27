// include/rooms/ShopRoom.h
#ifndef SHOPROOM_H
#define SHOPROOM_H

#include "Room.h"

// a room where the player can spend gold on cards and relics. not yet implemented
class ShopRoom : public Room {
public:
    ShopRoom(const std::string& description);
};

#endif
