#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor() : message_processor(messages,gameManager), socket(true){
	this->message_processor.start();
}

void ThreadAcceptor:: run() {
	
	int resultado = this->socket.acceptOn("localhost","666");
	
	std::cout << "Acceptor socket opened:" << resultado << std::endl;
	
    while (keep_running) {
		
        this->acceptConnection();
        
        this->gameManager.cleanUpDeadGames();
    }
}

void ThreadAcceptor::acceptConnection(){
	Socket clientSocket(this->socket.getReceiveSocket());
	std::string socket; //solo como placeholder, esto traeria el Socket real
	//if (this->gameManager.clients_counter < 3)
		this->gameManager.acceptClient(clientSocket, this->messages);
    
}

ThreadAcceptor:: ~ThreadAcceptor() {}
