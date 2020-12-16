#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>
#include <vector>

#include "Texture.h"

class Animation {
private:
	Texture sprite_sheet;
	uint current_frame;
	std::vector<SDL_Rect> frames;
	int frame_width;
	int frame_height;
public:
	Animation(SDL_Renderer* renderer, const char* sheet_filepath, 
						int frame_width, int frame_height, int n_frames);
	~Animation();
	void renderNextFrame(SDL_Renderer* renderer, int scale,
											 int x_pos, int y_pos);
};

#endif