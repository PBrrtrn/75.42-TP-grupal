#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor() : message_processor(messages,gameManager)
{
	this->message_processor.start();
}

void ThreadAcceptor:: run() {
	std::cout << "Acceptor receiving in socket. (mock!)" << std::endl;
    while (keep_running) {
		
        this->acceptConnection();
        
        this->gameManager.cleanUpDeadGames();
    }
}



void ThreadAcceptor::acceptConnection(){
	std::string socket; //solo como placeholder, esto traeria el Socket real
	if (this->gameManager.clients_counter < 3)
		this->gameManager.acceptClient(socket, this->messages);
    
}

ThreadAcceptor:: ~ThreadAcceptor() {

}
