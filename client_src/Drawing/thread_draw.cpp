#include "thread_draw.h"

ThreadDraw:: ThreadDraw(GameStatus& gStatus, Drawer& drawer, int clientID) :
gStatus(gStatus), drawer(drawer), clientID(clientID) {}

void ThreadDraw:: run() {
    while (running) {
        this->drawer.draw(gStatus, clientID);
	}
}

void ThreadDraw:: stop() {
    this->running = false;
}

ThreadDraw:: ~ThreadDraw(){}
