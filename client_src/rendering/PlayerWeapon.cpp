#include <iostream>

#include <vector>
#include <string>

#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(YAML::Node spec, SDL_Renderer* renderer) {
  std::string dir = spec["directory"].as<std::string>();

  std::vector<std::string> idle_paths;
  for (int i = 0; i < spec["idle"].size(); i++) {
    std::string path = dir + spec["idle"][i].as<std::string>();
    idle_paths.push_back(path);
  }
  this->idle_animation = new Animation(renderer, idle_paths);

  std::vector<std::string> shooting_paths;
  for (int i = 0; i < spec["shooting"].size(); i++) {
    std::string path = dir + spec["shooting"][i].as<std::string>();
    shooting_paths.push_back(path);
  }
  this->shooting_animation = new TimedAnimation(renderer, shooting_paths, 12);
}

PlayerWeapon::~PlayerWeapon() {
  delete this->idle_animation;
  delete this->shooting_animation;
}

void PlayerWeapon::renderIdle(SDL_Renderer* renderer) {
  this->shooting_animation->reset();
  this->idle_animation->render(renderer, 120, 310, 420, 120);
}

void PlayerWeapon::renderShooting(SDL_Renderer* renderer) {
  this->shooting_animation->render(renderer, 120, 310, 420, 120);
}