#include "message_processor.h"

#include <unistd.h>

MessageProcessor::MessageProcessor(BlockingQueue<std::string>& m) : messages(m)
	{}
	
void MessageProcessor::run(){

	std::cout << "Message Processor running. (mock!)" << std::endl;
    while (keep_running) {
        
        this->checkNews();
		usleep(3000);
    }	
	
}

void MessageProcessor::checkNews(){
	std::cout << this->messages.pop() << std::endl;

}

MessageProcessor::~MessageProcessor(){}
