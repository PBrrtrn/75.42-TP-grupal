#include "message_processor.h"

MessageProcessor::MessageProcessor(BlockingQueue<Message>& m, GameManager& gm) : 
messages(m), gameManager(gm), keep_running(true) {}
	
void MessageProcessor::run(){
	std::cout << "Message Processor running." << std::endl;
    while (keep_running) {
        this->checkNews();
    }	
}

void MessageProcessor::checkNews() {
	/*
	this->messages.lock();
	while (!this->messages.isEmptySync()) {
		Message m = this->messages.popSync();
		this->gameManager.newMessage(m);
	}
	this->messages.unlock();
	*/
	//REEMPLZAR POR PTRORECETD
}

void MessageProcessor::shutdown(){
	this->keep_running = false;
}

MessageProcessor::~MessageProcessor(){}
