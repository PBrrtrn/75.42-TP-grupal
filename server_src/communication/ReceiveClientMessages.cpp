#include "ReceiveClientMessages.h"

ReceiveClientMessages::ReceiveClientMessages(int clientId,Socket&& socket, BlockingQueue<Message>* serverMessages) :
    peer(std::move(socket)), 
    keep_running(true), 
    serverMessages(serverMessages),id(clientId) {
	this->messages = NULL;	
	}

void ReceiveClientMessages::assignToGameQueue(ProtectedQueue<Message>* messages) {
    this->messages = messages;
}

Socket& ReceiveClientMessages::getPeerReference() {
    return this->peer;
}

void ReceiveClientMessages::run() {
    while (this->keep_running) {
        ClientMessage client_message;
        int received = this->peer.socket_receive((char*)&client_message, 
                                                 sizeof(ClientMessage));

        if (received < sizeof(ClientMessage)) {
            std::cout << "Client exit game! No messages received (socket closed)" << std::endl;
            this->shutdown();
        } else {
            Message m(client_message.type, client_message.entityId, this->id);
            
            if (this->messages != NULL){
				this->messages->push(m);
			}
			else {
				this->serverMessages->push(m);
			}
        }
    }
}

void ReceiveClientMessages::shutdown() {
    this->keep_running = false;
    this->peer.close_socket();
}

ReceiveClientMessages::~ReceiveClientMessages() {}
