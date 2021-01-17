#include "thread_game.h"

ThreadGame:: ThreadGame(int gameId,BlockingQueue<Message>* m) : 
id(gameId), messages(m),gameStatus("./maps/map-data.yml") {}

void ThreadGame:: run() {
	
	this->keep_running = true;
	
	std::cout << "Game started!" << std::endl;
    while (keep_running) {
        
        this->checkNews();
    }
}

GameStatus ThreadGame:: getGameStatus() {
	return this->gameStatus;
}

void ThreadGame::checkNews(){
	
	Message m = this->messages->pop();
	std::cout << "en el game: " << (char)m.getType() << ", client:" << m.getClientId() << std::endl;
	
	switch (m.getType())
	{
	case TYPE_MOVE_FORWARD:
		this->tryMoveForward(m.getClientId());
		break;

	case TYPE_EXIT_GAME:
		this->expelClient(m.getClientId());
		break;

	default:
		break;
	}
	
	//agregar otras acciones
	    /*if (message.getMessage() == "w") {
        this->games.at(gameId)->tryMoveForward(message.getClientId());
    } else if (message.getMessage() == "a") {
        this->games.at(gameId)->tryMoveLeft(message.getClientId());
    } else if (message.getMessage() == "d") {
        this->games.at(gameId)->tryMoveRight(message.getClientId());
    } else if (message.getMessage() == "s") {
        this->games.at(gameId)->tryMoveBackward(message.getClientId());
    }*/
}

void ThreadGame::expelClient(int id){
	this->clients.erase(id);	
	if (this->clients.size() == 0)
		this->keep_running = false;
	//todo: keep_running = false si no hay mas clientes
}

void ThreadGame::addClient(ThreadClient* client, int id){
	this->clients.insert({id,client});
	Vector position(3,4);
	Vector direction(1,0);
	this->gameStatus.addPlayer(id, position, direction);
}

void ThreadGame::tryMoveForward(int id) {
    this->move_forward.tryAction(this->gameStatus, id );
}

void ThreadGame::tryMoveBackward(int id) {
    this->move_backward.tryAction(this->gameStatus, id );
}

void ThreadGame::tryMoveLeft(int id) {
    this->move_left.tryAction(this->gameStatus, id );
}

void ThreadGame::tryMoveRight(int id) {
    this->move_right.tryAction(this->gameStatus, id );
}

void ThreadGame::tryShoot(int id) {}

ThreadGame:: ~ThreadGame(){}
