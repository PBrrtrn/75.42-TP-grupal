#include "thread_game.h"

// TODO pasar a configuration
#define STEP 5
#define ROTATION_LEFT 15
#define ROTATION_RIGHT -15

ThreadGame:: ThreadGame() : clientCounter(0){}

void ThreadGame:: run() {}

void ThreadGame::addClient(Client *client){
	this->clients.push_back(client);
	this->gs.setPosition(this->clientCounter, 150, 150);
	this->gs.setAngle(this->clientCounter, 0);
	client->startGame(this->gs, clientCounter);
	clientCounter++;
}

bool ThreadGame:: _is_colision(int id, Vector& next_position) {
    if (this->map.isWall(next_position.getXCoordinate(), next_position.getYCoordinate())) {
        std::cout << "Wall detected - invalid move" << '\n';
        //TODO como imprimir mensaje en pantalla
        return true;
    } else if (/*agregar !isObject y funcion en map*/) {
        std::cout << "Object detected - invalid move" << '\n';
    } else {
        this->gameStatus.setPosition(id, next_position);
        return false;
    }
} 

void ThreadGame::tryMoveForward(int id) {
	Vector pos = this->gameStatus.getPosition(id);
	Vector angle = this->gameStatus.getAngle(id);
    angle.turnUnitary();
    Vector next_position = pos + (angle * STEP);
    _is_colision(id, next_position);
}

void ThreadGame::tryMoveBackward(int id) {
	Vector pos = this->gameStatus.getPosition(id);
	Vector angle = this->gameStatus.getAngle(id);
    angle.turnUnitary();
    Vector next_position = pos - (angle * STEP);
    _is_colision(id, next_position);
}

void ThreadGame:: _rotate_and_move(const int rotation_angle, int id) {
    Vector pos = this->gameStatus.getPosition(id);
	float angle = this->gameStatus.getAngle(id);
    angle += rotation_angle;
    Vector next_position = pos + (angle * STEP);
    if (!_is_colision(id, next_position)) {
        this->gameStatus.setAngle(id, angle);
    }
}

void ThreadGame::tryMoveLeft(int id) {
    _rotate_and_move(ROTATION_LEFT, id);
}

void ThreadGame::tryMoveRight(int id) {
    _rotate_and_move(ROTATION_RIGHT, id);
}

void ThreadGame::tryShoot(int id) {}

void ThreadGame:: _parse_message(std::string message) {
    if (message == "w") {
        this->move_forward.tryAction(*this);
    } else if (message == "a") {
        this->move_left.tryAction(*this);
    } else if (message == "d") {
        this->move_right.tryAction(*this);
    } else if (message == "s") {
        this->move_backward.tryAction(*this);
    }
}

void ThreadGame::newAction(std::string message) {
    this->_parse_message(message);
}

ThreadGame:: ~ThreadGame(){}
