#ifndef __GAME_RENDERER_H__
#define __GAME_RENDERER_H__

#include <vector>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "MapDrawer.h"
#include "Font.h"
#include "Animation.h"
#include "Texture.h"
#include "../game_status/GameStatusMonitor.h"
#include "../../common_src/Map.h"

class GameRenderer {
private:
	SDL_Renderer* renderer;
	YAML::Node config;
	GameStatusMonitor& game_status_monitor;
	Map map;
	std::vector<Animation*> animations;
	std::vector<Texture*> wall_textures;
	MapDrawer map_drawer;
	void load();
public:
	GameRenderer(SDL_Renderer* renderer, YAML::Node config,
							 GameStatusMonitor& game_status_monitor);
	~GameRenderer();
	void render();

};

#endif