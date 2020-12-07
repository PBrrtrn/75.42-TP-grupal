#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>

#include "Thread.h"
#include "EventQueue.h"

class Renderer : public Thread {
private:
	SDL_Renderer* renderer;
	Window window;
	EventQueue& event_queue;
public:
	Renderer(const char *title, int width, int height, EventQueue& event_queue);
	~Renderer();
	void run();
};

#endif
