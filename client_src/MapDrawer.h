#ifndef __MAP_DRAWER_H__
#define __MAP_DRAWER_H__

#include <vector>
#include <SDL2/SDL.h>

#include "../common_src/Map.h"
#include "../common_src/Vector.h"

class MapDrawer {
private:
	int screen_width;
	int screen_height;
	float field_of_view;
	std::vector<int> z_buffer;
public:
	MapDrawer(int screen_width, int screen_height, float field_of_view);
	~MapDrawer();
	std::vector<int> draw(SDL_Renderer* renderer, Map& map, 
												Vector position, float angle);
};

#endif