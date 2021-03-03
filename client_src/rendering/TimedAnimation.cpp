#include "TimedAnimation.h"

TimedAnimation::TimedAnimation(SDL_Renderer* renderer, 
								 							 std::vector<std::string> frame_paths,
								 							 int steps_per_frame)
: animation(renderer, frame_paths), steps(0), 
	steps_per_frame(steps_per_frame) { }

TimedAnimation::~TimedAnimation() { }

void TimedAnimation::render(SDL_Renderer* renderer, 
         										int x_pos, int y_pos, 
         										int width, int height) {
	if (((this->steps + 1) % steps_per_frame) == 0)
		this->animation.renderNextFrame(renderer, x_pos, y_pos, width, height);
	else
		this->animation.render(renderer, x_pos, y_pos, width, height);

	this->steps = (this->steps + 1) % steps_per_frame;
}

void TimedAnimation::reset() {
	this->steps = 0;
}
