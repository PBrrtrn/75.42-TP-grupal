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
            std::cout << "recv en threadclient fallo, no recibi nada! (cerro el socket?)" << std::endl;
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
