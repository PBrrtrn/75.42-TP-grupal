#ifndef __PLAYER_WEAPON_H__
#define __PLAYER_WEAPON_H__

#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "Animation.h"
#include "TimedAnimation.h"

class PlayerWeapon {
private:
  Animation* idle_animation;
  TimedAnimation* shooting_animation;
public:
  PlayerWeapon(YAML::Node spec, SDL_Renderer* renderer);
  ~PlayerWeapon();
  void renderIdle(SDL_Renderer* renderer);
  void renderShooting(SDL_Renderer* renderer);
};

#endif