#ifndef __DOOR_SERIALIZER_H_
#define __DOOR_SERIALIZER_H_

#include <sstream>
#include "door.h"

class DoorSerializer {
    public:
        DoorSerializer();
        Door deserialize(const std::string& serializedDoor);
        std::string serialize(Door& door);
        ~DoorSerializer();
};

#endif
