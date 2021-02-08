#ifndef __SPAWNPOINT_SERIALIZER_H_
#define __SPAWNPOINT_SERIALIZER_H_

#include <sstream>
#include "SpawnPoint.h"

class SpawnPointSerializer {
    public:
        SpawnPointSerializer();
        SpawnPoint deserialize(const std::string& serializedDoor);
        std::string serialize(SpawnPoint& spawnPoint);
        ~SpawnPointSerializer();
};

#endif
