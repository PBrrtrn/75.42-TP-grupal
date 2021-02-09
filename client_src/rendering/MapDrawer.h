#ifndef __MAP_DRAWER_H__
#define __MAP_DRAWER_H__

#include <vector>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.h"
#include "Animation.h"
#include "../../common_src/RayCaster.h"
#include "../../common_src/Map.h"
#include "../../common_src/Vector.h"
#include "../../common_src/ClientGameStatusElements.h"

class MapDrawer {
private:
	int screen_width;
	int screen_height;
	float fov;
	float wall_height;
	std::vector<Texture*>& wall_textures;
	std::vector<Animation*>& enemy_animations;
	RayCaster ray_caster;
public:
	MapDrawer(YAML::Node& config, std::vector<Texture*>& wall_textures,
						std::vector<Animation*>& enemy_animations);
	~MapDrawer();
	void draw(SDL_Renderer* renderer, Map& map, 
						Vector position, float view_angle,
						std::vector<PlayerListItem>& enemies);
};

#endif