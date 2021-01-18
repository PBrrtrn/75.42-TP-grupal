#ifndef __RAY_CASTER_H__
#define __RAY_CASTER_H__

#include "Map.h"
#include "Vector.h"

struct RayHit {
	float distance;
	int texture;
	float texel;
	int side;
};

class RayCaster {
public:
	RayCaster();
	~RayCaster();
	RayHit castRay(Map& map, Vector start_position, float angle);
};

#endif