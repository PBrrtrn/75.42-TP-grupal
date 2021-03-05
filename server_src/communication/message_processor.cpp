#include "message_processor.h"

MessageProcessor::MessageProcessor(GameManager& gm) : 
gameManager(gm), keep_running(true) {}
	
void MessageProcessor::run(){
    while (keep_running) {
        this->gameManager.receiveMessages();
    }	
}

void MessageProcessor::shutdown(){
	this->gameManager.closeBlockingQueue();
	this->keep_running = false;
}

MessageProcessor::~MessageProcessor(){}
