#ifndef __MAP_DRAWER_H__
#define __MAP_DRAWER_H__

#include <vector>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.h"
#include "../common_src/RayCaster.h"
#include "../common_src/Map.h"
#include "../common_src/Vector.h"

class MapDrawer {
private:
	int screen_width;
	int screen_height;
	float fov;
	float wall_height;
	std::vector<Texture*>& wall_textures;
	RayCaster ray_caster;
public:
	MapDrawer(YAML::Node& config, std::vector<Texture*>& wall_textures);
	~MapDrawer();
	std::vector<float> draw(SDL_Renderer* renderer, Map& map, 
													Vector position, float view_angle);
};

#endif