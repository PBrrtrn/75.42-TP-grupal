#include "Animation.h"

Animation::Animation(SDL_Renderer* renderer, const char* sheet_filepath,
                     int frame_width, int frame_height, int n_frames)
: sprite_sheet(renderer, sheet_filepath), current_frame(0),
  frame_width(frame_width), frame_height(frame_height) {
  this->frames.reserve(n_frames);
  for (int i = 0; i < n_frames; i++) {
    SDL_Rect frame { 0, i*frame_height, frame_width, frame_height };
    this->frames.push_back(frame);
  }
}

Animation::~Animation() { }

void Animation::renderNextFrame(SDL_Renderer* renderer, int scale,
                                int x_pos, int y_pos) {
  int frame_n = (current_frame + 1) % this->frames.size();

  SDL_Rect dest { x_pos, y_pos, 
                  this->frame_width*scale,
                  this->frame_height*scale };

  this->sprite_sheet.render(renderer, &frames[frame_n], &dest);
  this->current_frame += 1;
}
