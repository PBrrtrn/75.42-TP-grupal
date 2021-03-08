#include <iostream>

#include "Animation.h"

Animation::Animation(SDL_Renderer* renderer, 
                     std::vector<std::string> frame_paths) {
  this->frames.reserve(frame_paths.size());
  for (std::string& frame_path : frame_paths) {
    this->frames.push_back(new Texture(renderer, frame_path.c_str()));
  }
}

Animation::~Animation() {
  for (Texture* frame : this->frames) delete frame;
}

void Animation::render(SDL_Renderer* renderer, int frame,
                       int x_pos, int y_pos, int width, int height) {
  int frame_n = frame % this->frames.size();
  SDL_Rect dest { x_pos, y_pos, width, height };
  this->frames[frame_n]->render(renderer, NULL, &dest);
}

void Animation::renderTexels(SDL_Renderer* renderer, int frame,
                             std::vector<float>& z_buffer,
                             float z_depth, int x_pos, int y_pos,
                             int width, int height) {
  int frame_n = frame % this->frames.size();
  Texture* texture = this->frames[frame_n];

  texture->renderTexels(renderer, z_buffer, z_depth, 
                        x_pos, y_pos, width, height);
}

int Animation::framesCount() {
  return this->frames.size();
}
