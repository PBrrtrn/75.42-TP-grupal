#ifndef __UI_DRAWER_H__
#define __UI_DRAWER_H__

#include <vector>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "../game_status/GameStatusMonitor.h"
#include "Font.h"
#include "Animation.h"
#include "Texture.h"

class UIDrawer {
private:
	Texture* ui_bar_texture;
	SDL_Rect ui_bar_dimensions;
	Texture* key_icon_texture;
	SDL_Rect key_icon_dimensions;
	Font* font;
	void load(SDL_Renderer* renderer, YAML::Node config);
public:
	UIDrawer(SDL_Renderer* renderer, YAML::Node config);
	~UIDrawer();
	void draw(SDL_Renderer* renderer, uint8_t health, uint8_t enemies_alive, 
						uint8_t ammo, uint8_t lives, bool has_key);
};

#endif