#include "message_processor.h"


MessageProcessor::MessageProcessor(BlockingQueue<Message>& m) : messages(m)
	{}
	
void MessageProcessor::run(){

	std::cout << "Message Processor running. (mock!)" << std::endl;
    while (keep_running) {
        this->checkNews();
    }	
	
}

void MessageProcessor::checkNews(){
	
	Message m = this->messages.pop();
	std::cout << m.getMessage() << m.getClientId() << std::endl;
	
	this->gameManager.newMessage(m);
	
}

MessageProcessor::~MessageProcessor(){}
