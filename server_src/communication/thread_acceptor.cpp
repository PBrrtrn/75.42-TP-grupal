#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor(/*const Socket& s, */BlockingQueue<std::string>& messages) :
messages(messages) {
    //this->socket = s;
    this->clients_counter = 0;
}

void ThreadAcceptor:: run() {
    while (keep_running) {
        /*
        Socket* peer = new Socket();
        if (peer->socket_accept(&this->socket) < 0) {
            delete peer;
            break;
        }
        */
        //TODO VER CÓMO CREAR HILO PARTIDA Y UN GAME STATUS POR CADA UNO
        this->newClient();
        //this->garbage_collector();
        if (this->clients_counter == 2) keep_running = false; //HARDCODED
    }
}

void ThreadAcceptor:: newMessage(std::string message, int clientID) {
    this->_parse_message(message, clientID); //por ahora cout msg
    //if action == new game
    //new th_game(id client)
    //else gameclient(action)
}

void ThreadAcceptor:: _parse_message(std::string message, int clientID) {
    if (message == "w") {
        this->clientsGames.at(clientID)->tryMoveForward(clientID);
    } else if (message == "a") {
        this->clientsGames.at(clientID)->tryMoveLeft(clientID);
    } else if (message == "d") {
        this->clientsGames.at(clientID)->tryMoveRight(clientID);
    } else if (message == "s") {
        this->clientsGames.at(clientID)->tryMoveBackward(clientID);
    }
}

void ThreadAcceptor::newClient(){
    //this->clientsThreads.insert({this->clients_counter, 
	//	new ThreadClient(this->clients_counter, messages)});
		//new ThreadClient(this->clients_counter, messages)});
        //new ThreadClient(*this, this->clients_counter, messages)});
    //this->clientsThreads.at(this->clients_counter)->start();
    //this->clients_counter++;
}

ThreadAcceptor:: ~ThreadAcceptor() {
    //for (auto& x: clientsThreads) {
    //    x.second->join();
    //    delete x.second;
    //}
}
