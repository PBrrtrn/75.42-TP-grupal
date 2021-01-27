#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor() : message_processor(messages,gameManager){
	this->message_processor.start();
}

void ThreadAcceptor:: run() {
	
	bool resultado = this->socket.socket_bind_and_listen("localhost","666");
	
	std::cout << "Acceptor socket opened:" << (resultado ? 0 : -1) << std::endl;
	
    while (keep_running) {
		
        this->acceptConnection();
        
        this->gameManager.cleanUpDeadGames();
    }
}

void ThreadAcceptor::acceptConnection(){
	Socket peer;
	if (peer.socket_accept(this->socket) > 0) {
		this->gameManager.acceptClient(peer, this->messages);
	}
}

ThreadAcceptor:: ~ThreadAcceptor() {}
