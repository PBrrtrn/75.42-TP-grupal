#include <iostream>
#include <math.h>

#include "RayCaster.h"

RayCaster::RayCaster() { }

RayCaster::~RayCaster() { }

RayHit RayCaster::castRay(Map& map, Vector position, float angle) {
	int map_column = int(position.x);
	int map_row = int(position.y);

	float ray_x = cos(angle);
	float ray_y = sin(angle);

	float columnwise_delta = std::abs(1/ray_x);
	float rowwise_delta = std::abs(1/ray_y);

	float first_column_distance;
	int columnwise_step;
	if (ray_x > 0) {
		columnwise_step = 1;
		first_column_distance = 1 - (position.x - map_column);
	} else {
		columnwise_step = -1;
		first_column_distance = (position.x - map_column);
	}

	float first_row_distance;
	int rowwise_step;
	if (ray_y > 0) {
		rowwise_step = -1;
		first_row_distance = (position.y - map_row);
	} else {
		rowwise_step = 1;
		first_row_distance = 1 - (position.y - map_row);
	}

	float columnwise_distance = first_column_distance * columnwise_delta;
	float rowwise_distance = first_row_distance * rowwise_delta;

	int hit_side;
	while (map[map_row][map_column] < 1) {
		if (columnwise_distance < rowwise_distance) {
			map_column += columnwise_step;
			columnwise_distance += columnwise_delta;
			hit_side = 0;
		} else {
			map_row += rowwise_step;
			rowwise_distance += rowwise_delta;
			hit_side = 1;
		}
	}

	int texture = map[map_row][map_column] - 1;

	float distance;
	if (hit_side == 0) {
	  distance = map_column - position.x + (1 - columnwise_step)/2;
	  distance = distance * columnwise_delta;
	}	else {
		distance = (position.y - (1 - rowwise_step)/2 - map_row) * rowwise_delta;
	}

	float texel;
	if (hit_side == 0) texel = position.y + distance * ray_y;
	else texel = position.x + distance * ray_x;
	texel -= floor(texel);

	// std::cout << distance << std::endl;
	return RayHit { distance, texture, texel, hit_side };
}
