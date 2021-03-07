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

  int start_x = x_pos - (width/2);
  int end_x = x_pos + (width/2);
  for (int texel_x = start_x; (texel_x < end_x) && (texel_x < 640); texel_x++) {
    if (z_depth < z_buffer[texel_x]) {
      float texel = ((float)(texel_x - start_x))/(float(texture->getWidth()));
      texture->renderTexel(renderer, texel_x, texel, 480, height, 0);
    }
  }
}

int Animation::framesCount() {
  return this->frames.size();
}
