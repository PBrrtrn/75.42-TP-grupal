#ifndef __PLAYER_WEAPON_H__
#define __PLAYER_WEAPON_H__

#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "Animation.h"
#include "TimedAnimation.h"

class PlayerWeapon {
private:
	int sprite_x_pos;
	int sprite_y_pos;
	int sprite_width;
	int sprite_height;
  Animation* idle_animation;
  TimedAnimation* shooting_animation;
  bool shooting;
  int total_shooting_steps;
  int elapsed_shooting_steps;
public:
  PlayerWeapon(YAML::Node spec, SDL_Renderer* renderer);
  ~PlayerWeapon();
  void setShooting();
  void render(SDL_Renderer* renderer);
};

#endif