#include <iostream>

#include "Animation.h"

Animation::Animation(SDL_Renderer* renderer, 
                     std::vector<std::string> frame_paths) : current_frame(0) {
  this->frames.reserve(frame_paths.size());
  for (std::string& frame_path : frame_paths) {
    std::cout << frame_path << std::endl;
    this->frames.push_back(new Texture(renderer, frame_path.c_str()));
  }
}

Animation::~Animation() {
  for (Texture* frame : this->frames) delete frame;
}

void Animation::render(SDL_Renderer* renderer, 
                       int x_pos, int y_pos, 
                       int width, int height) {
  SDL_Rect dest { x_pos, y_pos, width, height };
  this->frames[this->current_frame]->render(renderer, NULL, &dest);
}

void Animation::renderTexel(SDL_Renderer* renderer, 
                            std::vector<float>& z_buffer,
                            float z_depth, int x_pos, int y_pos, 
                            int width, int height) {
  Texture* frame = this->frames[0];

  int start_x = x_pos - (frame->getWidth()/2);
  int end_x = x_pos + (frame->getWidth()/2);
  for (int texel_x = start_x; (texel_x < end_x) && (texel_x < 640); texel_x++) {
    if (z_depth < z_buffer[texel_x]) {
      float texel = ((float)(texel_x - start_x))/(float(frame->getWidth()));
      frame->renderTexel(renderer, texel_x, texel, 480, height, 0);
    }
  }
}
