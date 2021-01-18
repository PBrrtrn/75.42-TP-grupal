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

	case TYPE_MOVE_BACKWARD:
		this->tryMoveBackward(m.getClientId());
		break;
	
	case TYPE_MOVE_LEFT:
		this->tryMoveLeft(m.getClientId());
		break;

	case TYPE_MOVE_RIGHT:
		this->tryMoveRight(m.getClientId());
		break;

	case TYPE_EXIT_GAME:
		this->expelClient(m.getClientId());
		break;
	
	case TYPE_SHOOT:
		this->tryShoot(m.getClientId());
		break;

	default:
		break;
	}

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
