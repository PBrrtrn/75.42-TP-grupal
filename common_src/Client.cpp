#include "Client.h"
#include "Server.h"
#include "Actions/ActionMoveForward.h"
#include "Actions/ActionMoveBackward.h"
#include "Actions/ActionRotateLeft.h"
#include "Actions/ActionRotateRight.h"

Client::Client(Server &server) : thSend(send_queue, server) {
	server.addClient(this);
}

Client::~Client(){
	this->send_queue.close();
	this->thSend.join();
}

void Client::startGame(GameStatus& gStatus, int clientID) {
    this->id = clientID;
	this->thSend.start();
	ThreadDraw thDrawer(gStatus, this->drawer, clientID);
	thDrawer.start();

	SDL_Event event;
	bool running = true;

	while (running) {
		SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN: {
				SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
				switch (keyEvent.keysym.sym) {
					case SDLK_w:
						std::cout << "W PRESSED" << std::endl;
						this->send_queue.push(new ActionMoveForward(this->id));
						break;
                    case SDLK_s:
                        std::cout << "S PRESSED" << std::endl;
                        this->send_queue.push(new ActionMoveBackward(this->id));
                        break;
                    case SDLK_a:
                        std::cout << "A PRESSED" << std::endl;
                        this->send_queue.push(new ActionRotateLeft(this->id));
                        break;
                    case SDLK_d:
                        std::cout << "d PRESSED" << std::endl;
                        this->send_queue.push(new ActionRotateRight(this->id));
                        break;
					case SDLK_q:
						std::cout << "Quit :(" << std::endl;
		                running = false;
		                break;
				}
			}
				break;

			case SDL_QUIT:
				std::cout << "Quit :(" << std::endl;
                running = false;
                break;
		}
	}
	thDrawer.stop();
	thDrawer.join();
}
