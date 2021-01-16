#include "message_processor.h"


MessageProcessor::MessageProcessor(BlockingQueue<Message>& m, GameManager& gm) : messages(m), gameManager(gm)
	{}
	
void MessageProcessor::run(){

	std::cout << "Message Processor running." << std::endl;
    while (keep_running) {
        this->checkNews();
    }	
	
}

void MessageProcessor::checkNews(){
	
	Message m = this->messages.pop();
	std::cout << "En processor. Mensaje:"<< (char)m.getType()<< ", cliente:" << m.getClientId() << std::endl;
	
	this->gameManager.newMessage(m);
	
}

MessageProcessor::~MessageProcessor(){}
