// include/rooms/EventRoom.h
#ifndef EVENTROOM_H
#define EVENTROOM_H

#include "Room.h"

// a room with a story event and choices. not yet implemented
class EventRoom : public Room {
public:
    EventRoom(const std::string& description);
};

#endif
