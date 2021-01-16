#include "thread_game.h"

ThreadGame:: ThreadGame(int gameId,BlockingQueue<Message>* m) : id(gameId),messages(m) {}

void ThreadGame:: run() {
	
	bool keep_running = true;
	
	std::cout << "Game started!" << std::endl;
    while (keep_running) {
        
        this->checkNews();
     
    }
	
}

void ThreadGame::checkNews(){
	
	Message m = this->messages->pop();
	std::cout << "en el game: " << m.getMessage() << "client" << m.getClientId() << std::endl;
	
	//this->gameManager.newMessage(m);
	
}

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
