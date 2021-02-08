#ifndef __SPAWNPOINT_H_
#define __SPAWNPOINT_H_

#include "../../common_src/Vector.h"

class SpawnPoint {
private:
    Vector position;
    Vector direction;
public:
	SpawnPoint(Vector position,Vector direction);
	Vector getPosition();
	Vector getDirection();
	~SpawnPoint();
};

#endif
