#include "thread_game.h"

ThreadGame:: ThreadGame() : clientCounter(0){}

void ThreadGame:: run() {}

void ThreadGame::addClient(Client *client){
	this->clients.push_back(client);
	this->gameStatus.setPosition(this->clientCounter, 150, 150);
	this->gameStatus.setAngle(this->clientCounter, 0);
	client->startGame(this->gameStatus, clientCounter);
	clientCounter++;
}

void ThreadGame::tryMoveForward(int id) {
    this->move_forward.tryAction(this->gameStatus, id, this->map);
}

void ThreadGame::tryMoveBackward(int id) {
    this->move_backward.tryAction(this->gameStatus, id, this->map);
}

void ThreadGame::tryMoveLeft(int id) {
    this->move_left.tryAction(this->gameStatus, id, this->map);
}

void ThreadGame::tryMoveRight(int id) {
    this->move_right.tryAction(this->gameStatus, id, this->map);
}

void ThreadGame::tryShoot(int id) {}

ThreadGame:: ~ThreadGame(){}
