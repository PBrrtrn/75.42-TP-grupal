#ifndef __MAP_DRAWER_H__
#define __MAP_DRAWER_H__

#include <vector>
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.h"
#include "EnemyEntity.h"
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
	std::vector<Texture*>& item_sprites;
	Map& map;
	RayCaster ray_caster;
	void drawFloors(SDL_Renderer* renderer);
	void drawEnemies(SDL_Renderer* renderer, 
									 Vector position, float view_angle,
                   std::unordered_map<char, EnemyEntity*> enemies,
                   std::vector<float> z_buffer);
	void drawItems(SDL_Renderer* renderer, 
                 Vector position, float view_angle,
                 std::vector<ItemListElement>& items,
                 std::vector<float> z_buffer);
public:
	MapDrawer(YAML::Node& config, Map& map,
						std::vector<Texture*>& wall_textures,
						std::vector<Texture*>& item_sprites);
	~MapDrawer();
	void draw(SDL_Renderer* renderer, Vector position, float view_angle,
						std::vector<ItemListElement>& items,
						std::unordered_map<char, EnemyEntity*> enemies);
};

#endif