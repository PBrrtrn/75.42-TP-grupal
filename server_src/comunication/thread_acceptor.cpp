#include "thread_acceptor.h"

ThreadAcceptor:: ThreadAcceptor(/*const Socket& s, */) {
    //this->socket = s;
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
        clients.push_back(new ThreadClient(/*peer, */));
        clients.back()->start();
        this->garbage_collector();
    }
}

void ThreadAcceptor::newClient(){
    this->clientsThreads.push_back(new ThreadClient(*this));
    this->clientsThreads.back()->start();
}

/*
void ThreadAcceptor:: garbage_collector() {
    std::list<ThreadClient*>::iterator it;
    it = this->clients.begin();
    while (it != this->clients.end()) {
        if ((*it)->is_dead()) {
            (*it)->stop();
            delete (*it);
            it = this->clients.erase(it);
        } else {
            ++it;
        }
    }
}
*/

/*
void ThreadAcceptor:: stop() {
    this->keep_running = false;
    //shutdown(this->socket.get_fd(), SHUT_RDWR);
    //close(this->socket.get_fd());
    std::list<ThreadClient*>::iterator it;
    for (it = this->clients.begin(); 
    it != this->clients.end(); ++it) {
        (*it)->join(); //TODO hacer stop
        delete (*it);
    }
}
*/

ThreadAcceptor:: ~ThreadAcceptor(){}
