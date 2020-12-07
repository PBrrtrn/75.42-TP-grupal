#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Texture.h"

class Animation {
private:
	/* TODO: recibir la textura por movimiento.
		 No tiene sentido que exista por fuera del objeto Animation 
															- Pablo (06/12/2020)					 */
	Texture& sprite_sheet;
	uint current_frame;
	std::vector<SDL_Rect> frames;
	int frame_width;
	int frame_height;
	int current_frame;
public:
	Animation(Texture& sprite_sheet, int frame_width, 
						int frame_height, int n_frames);
	~Animation();
	void renderNextFrame(SDL_Renderer* renderer, int x_pos, int y_pos);
};

#endif