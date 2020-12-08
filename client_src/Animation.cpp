#include "Animation.h"

Animation::Animation(Texture& sprite_sheet, int frame_width, 
										 int frame_height, int n_frames)
: sprite_sheet(sprite_sheet),
	current_frame(0),
  frame_width(frame_width),
  frame_height(frame_height) {
	this->frames.reserve(n_frames);
	for (int i = 0; i < n_frames; i++) {
		SDL_Rect frame { i*frame_width, 0, frame_width, frame_height };
		this->frames.push_back(frame);
	}
}

Animation::~Animation() { }

void Animation::renderNextFrame(SDL_Renderer* renderer, int x_pos, int y_pos) {
	// int frame_n = (current_frame + 1) % this->frames.size();
}
