#include "ThreadSend.h"
#include "Server.h"

ThreadSend:: ThreadSend(BlockingQueue<Action*>& messages, Server& server) :
messages(messages), server(server) {}

void ThreadSend:: run() {
    while(true) {
        try {
            Action* message = this->messages.pop();
            server.newAction(message);
            delete message;
            //server.keyPressed(message); //TODO send socket
        } catch (...) {
            break;
        }
    }
}

ThreadSend:: ~ThreadSend(){}
