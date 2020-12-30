#include "thread_client.h"
#include "server.h"

ThreadClient::ThreadClient(ThreadAcceptor& acceptor, int id) : acceptor(acceptor) {
    //this->peer = peer;
    this->id = id;
}

void ThreadClient::run() {

    char buffer[BUF_SIZE];
    ssize_t bytes_received = 0;

    while (keep_running){
        try {
            /*
            bytes_received = peer->socket_receive(buffer, BUF_SIZE);
            if (bytes_received < 0 || bytes_received == 0) {
                keep_running = false;
                break;
            }
            std::string str(buffer, bytes_received);
            */
            //TODO pasarle al acceptor a qué partida
            //quiere ir el cliente y los movimientos
            std::string message = this->messages.pop();
            acceptor.newMessage(message);

        } catch (...) {
            if (!keep_running) break;
        } 
    }
    //shutdown(peer->get_fd(), SHUT_WR);
    //dead = true; 
}

/*
void ThreadClient:: stop() {
    keep_running = false;
    delete this->peer;
}

bool ThreadClient:: is_dead() {
    return this->dead;
}
*/

ThreadClient:: ~ThreadClient(){
    this->join();
}
