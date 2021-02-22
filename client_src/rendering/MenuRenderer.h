#ifndef __MENU_RENDERER_H__
#define __MENU_RENDERER_H__

#include <vector>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "Font.h"
#include "Texture.h"
#include "../game_status/MenuStatus.h"
#include "../../common_src/LobbyStatusData.h"

class MenuRenderer {
private:
	YAML::Node config;
	MenuStatus& menu_status;
	SDL_Renderer* renderer;
	Font* font;
	Texture* background;
	void load();
	void renderGamesBox(int selected_option);
	void renderMapsBox(int selected_option);
	void renderLobbyBox(LobbyStatusData lobby_status);
	void renderGameOption(GameListItem& option, int y, bool highlight);
	void renderMapOption(MapListItem& option, int y, bool highlight);
public:
	MenuRenderer(YAML::Node config, 
							 MenuStatus& menu_status, 
							 SDL_Renderer* renderer);
	~MenuRenderer();
	void render();
};

#endif