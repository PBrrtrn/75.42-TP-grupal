#include <iostream>

#include <vector>
#include <string>

#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(YAML::Node spec, SDL_Renderer* renderer) 
: shooting(false), elapsed_steps(0) {
  // this->total_shooting_steps = spec["steps"].as<int>();
  this->shooting_steps_per_frame = 6; // Settear por config
  this->idle_steps_per_frame = 1;

  this->sprite_x_pos = spec["x_pos"].as<int>();
  this->sprite_y_pos = spec["y_pos"].as<int>();
  this->sprite_width = spec["width"].as<int>();
  this->sprite_height = spec["height"].as<int>();

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
  this->shooting_animation = new Animation(renderer, shooting_paths);

  std::string sound_path = dir + spec["sfx"].as<std::string>();
  this->shooting_sound = new SoundEffect(sound_path.c_str());
}

PlayerWeapon::~PlayerWeapon() {
  delete this->idle_animation;
  delete this->shooting_animation;
  delete this->shooting_sound;
}

void PlayerWeapon::setShooting() {
  this->elapsed_steps = 0;
  this->shooting = true;
  this->shooting_sound->play();
}

void PlayerWeapon::render(SDL_Renderer* renderer) {
  if (this->shooting) {
    int frame = ((this->elapsed_steps) / (this->shooting_steps_per_frame));
    this->shooting_animation->render(renderer, frame,
                                     this->sprite_x_pos, 
                                     this->sprite_y_pos,
                                     this->sprite_width,
                                     this->sprite_height);
    int frames_count = this->shooting_animation->framesCount();
    int total_shooting_steps = this->shooting_steps_per_frame * frames_count;
    if (this->elapsed_steps == total_shooting_steps) {
      this->elapsed_steps = 0;
      this->shooting = false;
    }
  } else {
    int frame = ((this->elapsed_steps) / (this->idle_steps_per_frame));
    this->idle_animation->render(renderer, frame,
                                 this->sprite_x_pos, 
                                 this->sprite_y_pos,
                                 this->sprite_width,
                                 this->sprite_height);
    int frames_count = this->shooting_animation->framesCount();
    int total_idle_steps = this->shooting_steps_per_frame * frames_count;
    this->elapsed_steps = this->elapsed_steps % total_idle_steps;
  }
  this->elapsed_steps++;
}
