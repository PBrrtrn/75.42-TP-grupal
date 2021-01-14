#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor(/*const Socket& s, BlockingQueue<std::string>& messages*/)
/*messages(messages)*/ {
    //this->socket = s;
    //this->clients_counter = 0;
}

void ThreadAcceptor:: run() {
	std::cout << "Acceptor receiving in socket. (mock!)" << std::endl;
    //while (keep_running) {
        /*
        Socket* peer = new Socket();
        if (peer->socket_accept(&this->socket) < 0) {
            delete peer;
            break;
        }
        */
        //TODO VER CÓMO CREAR HILO PARTIDA Y UN GAME STATUS POR CADA UNO
        //this->newClient();
        this->acceptConnection();
        //this->garbage_collector();
        //if (this->clients_counter == 2) keep_running = false; //HARDCODED
    //}
}

void ThreadAcceptor::acceptConnection(){
	std::string socket; //solo como placeholder, esto traeria el Socket real
	this->gameManager.acceptClient(socket);
    //this->clientsThreads.insert({this->clients_counter, 
	//	new ThreadClient(this, this->clients_counter, messages)});
    //this->clientsThreads.at(this->clients_counter)->start();
    //this->clients_counter++;
}

ThreadAcceptor:: ~ThreadAcceptor() {

}
