// include/rooms/Room.h
#ifndef ROOM_H
#define ROOM_H

#include <string>

class Enemy;

enum RoomType { ROOM_BATTLE, ROOM_EVENT, ROOM_TREASURE, ROOM_CAMPFIRE, ROOM_SHOP };

// one stop on the tower path
class Room {
public:
    Room(RoomType type, const std::string& description);
    virtual ~Room();
    RoomType getType() const { return type_; }
    const std::string& getDescription() const { return description_; }
    // only valid for ROOM_BATTLE. returns NULL for all other types. caller owns the pointer
    virtual Enemy* createEnemy() const;
private:
    RoomType type_;
    std::string description_;
};

#endif
