#include "server.h"
#include "vector.h"
#include <iostream>

// TODO pasar a configuration
#define STEP 5
#define ROTATION_LEFT 15
#define ROTATION_RIGHT -15

Server::Server() : clientCounter(0){}

Server::~Server(){
    std::vector<ThreadClient*>::iterator it;
    for (it = this->clientsThreads.begin();
         it != this->clientsThreads.end(); ++it) {
        (*it)->join();
        delete (*it);
    }
}

void Server::addClient(Client *client){
	this->clients.push_back(client);
	this->gameStatus.setPosition(this->clientCounter,96,96);
	this->gameStatus.setAngle(this->clientCounter, 1.047);
	client->startGame(this->gameStatus, clientCounter);
	clientCounter++;
}

void Server::newClient(){
    //TODO acceptor responsibility

    this->clientsThreads.push_back(new ThreadClient(*this));
    this->clientsThreads.back()->start();
}

static void _is_colision(int id, Vector& next_position) {
    if (this->map.isWall(next_position.getXCoordinate(), next_position.getYCoordinate())) {
        std::cout << "Wall detected - invalid move" << '\n';
        //TODO como imprimir mensaje en pantalla
        return true;
    } else {
        this->gameStatus.setPosition(id, next_position);
        return false;
    }
} 

void Server::tryMoveForward(int id) {
	Vector pos = this->gameStatus.getPosition(id);
	Vector angle = this->gameStatus.getAngle(id);
    angle.turnUnitary();
    Vector next_position = pos + (angle * STEP);
    _is_colision(id, next_position);
}

void Server::tryMoveBackward(int id) {
	Vector pos = this->gameStatus.getPosition(id);
	Vector angle = this->gameStatus.getAngle(id);
    angle.turnUnitary();
    Vector next_position = pos - (angle * STEP);
    _is_colision(id, next_position);
}

static void _rotate_and_move(const rotation_angle) {
    Vector pos = this->gameStatus.getPosition(id);
	Vector angle = this->gameStatus.getAngle(id);
    angle.turnUnitary();
    angle += rotation_angle;
    Vector next_position = pos + (angle * STEP);
    if (!_is_colision(id, next_position)) {
        this->gameStatus.setAngle(id, angle);
    }
}

void Server::tryMoveLeft(int id) {
    _rotate_and_move(ROTATION_LEFT);
}

void Server::tryMoveRight(int id) {
    _rotate_and_move(ROTATION_RIGHT);
}

void Server::tryShoot(int id) {}

void Server::newAction(Action action) {
    action.tryAction(*this);
}