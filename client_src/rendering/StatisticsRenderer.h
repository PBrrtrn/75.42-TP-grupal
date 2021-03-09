#ifndef __STATISTICS_RENDERER_H__
#define __STATISTICS_RENDERER_H__

#include <vector>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "Font.h"
#include "Texture.h"
#include "../../common_src/ClientGameStatusElements.h"

class StatisticsRenderer {
private:
	YAML::Node config;
	SDL_Renderer* renderer;
	Font* font;
	Texture* background;
    GameStatistics& statistics;
	void load();
	void renderStatisticsBox();
public:
	StatisticsRenderer(YAML::Node config, SDL_Renderer* renderer, GameStatistics& statistics);
	~StatisticsRenderer();
	void render();
};

#endif