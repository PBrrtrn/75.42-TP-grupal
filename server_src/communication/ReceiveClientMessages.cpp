#include "ReceiveClientMessages.h"

ReceiveClientMessages::ReceiveClientMessages(Socket&& socket, ProtectedQueue<Message>* messages) :
    peer(std::move(socket)), 
    keep_running(true), 
    messages(messages) {}

void ReceiveClientMessages::assignToGameQueue(ProtectedQueue<Message>* messages) {
    this->messages = messages;
}

Socket& ReceiveClientMessages::getPeerReference() {
    return this->peer;
}

void ReceiveClientMessages::run() {
    while (this->keep_running) {
        ClientMessage client_message;
        std::cout << "Receiving client message" << std::endl;
        int received = this->peer.socket_receive((char*)&client_message, 
                                                 sizeof(ClientMessage));
        std::cout << "Received client message" << std::endl;

        if (received < sizeof(ClientMessage)) {
            std::cout << "recv en threadclient fallo, no recibi nada! (cerro el socket?)" << std::endl;
            this->shutdown();
        } else {
            Message m(client_message.type, client_message.entityId, this->id);
            this->messages->push(m);
        }
        /*
        size_t size;
        int received = this->peer.socket_receive((char*)(&size), sizeof(size_t));
        
        ClientMessage cMessage;
        for (int i = 0; i < size / sizeof(cMessage); i++ ){				
            int received = this->peer.socket_receive((char*)(&cMessage), sizeof(cMessage));
            if (received < sizeof(cMessage)){
                std::cout << "recv en threadclient fallo, no recibi nada! (cerro el socket?)" << std::endl;
                this->shutdown();
            } else {
                Message m(cMessage.type, cMessage.entityId, this->id);
                this->messages->push(m);				
            }
        }
        */
    }
}

void ReceiveClientMessages::shutdown() {
    this->keep_running = false;
}

ReceiveClientMessages::~ReceiveClientMessages() {}
