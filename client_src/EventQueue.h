#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

#include <queue>
#include <mutex>

class EventQueue {
private:
	std::mutes;
	std::queue<SDL_Event> queue;
public:
	EventQueue();
	~EventQueue();
	void add(int event); // Modelar la clase evento
	int pop(); // Acá también, devolver una instancia de evento
};

#endif