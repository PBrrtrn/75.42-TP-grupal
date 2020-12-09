#include "Server.h"
#include "Vector.h"
#include <iostream>


#define MOVEMENT 5
#define ROTATION 0.0872665// TODO pasar a config
#define TEST_CLIENT_XPOS 127
#define TEST_CLIENT_YPOS 200

Server::Server() : clientCounter(0){
	
	MapData md("map-data.yml");
	Map m(md);
	
	this->map = m;
	
	}

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
	this->gameStatus.setPosition(this->clientCounter,TEST_CLIENT_XPOS,TEST_CLIENT_YPOS);
	this->gameStatus.setAngle(this->clientCounter, 1.047);
	client->startGame(this->gameStatus, clientCounter);
	clientCounter++;
}

void Server::newClient(){
    //TODO acceptor responsibility

    this->clientsThreads.push_back(new ThreadClient(*this));
    this->clientsThreads.back()->start();
}

void Server::tryMoveForward(int id) {
	this->tryMovement(id, 1);
}

void Server::tryMoveBackward(int id) {
    this->tryMovement(id, -1);
}

void Server::tryMovement(int id, int direction) {
    Vector pos = this->gameStatus.getPosition(id);
    Vector angle = this->gameStatus.getAngle(id);
    Vector nextPosition;
    angle.turnUnitary();
    nextPosition = pos + (angle * (MOVEMENT * direction));
    //TODO Server or GameStatus responsibility??
    if (this->gameStatus.isValidMovement(nextPosition)){
        this->gameStatus.setPosition(id, nextPosition);
    }
}

void Server::tryRotation(int id, int direction) {
    float angle = this->gameStatus.getAngle(id);
    this->gameStatus.setAngle(id, angle + (ROTATION * direction));
}

void Server::tryRotationLeft(int id) {
    this->tryRotation(id, 1);
}

void Server::tryRotationRight(int id) {
    this->tryRotation(id, -1);
}

void Server::newAction(Action* action) {
    action->tryAction(*this);
}
