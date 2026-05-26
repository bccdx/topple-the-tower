#include "Room.h"

Room::Room(RoomType type, const std::string& description) {
    type_ = type;
    description_ = description;
}

Room::~Room() {}

Enemy* Room::createEnemy() const {
    return NULL;
}
