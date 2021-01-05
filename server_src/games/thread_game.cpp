#include "thread_game.h"

ThreadGame:: ThreadGame() {}

void ThreadGame:: run() {}

void ThreadGame::addClient(ThreadClient* client, int id){
	this->clients.push_back(client);
	this->gameStatus.setPosition(id, 150, 150);
	this->gameStatus.setAngle(id, 0);
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
