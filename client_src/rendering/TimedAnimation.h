#ifndef __TIMED_ANIMATION_H__
#define __TIMED_ANIMATION_H__

#include <vector>

#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "Animation.h"

class TimedAnimation {
private:
	int steps;
	const int steps_per_frame;
	Animation animation;
public:
	TimedAnimation(SDL_Renderer* renderer, 
								 std::vector<std::string> frame_paths,
								 int steps_per_frame);
	~TimedAnimation();
	void render(SDL_Renderer* renderer, 
         			int x_pos, int y_pos, 
         			int width, int height);
	void reset();
};

#endif