#include "thread_client.h"

#include <unistd.h>  //removeme

ThreadClient::ThreadClient(int id, 
BlockingQueue<Message>& messages) : 
 messages(messages) {
    this->keep_running = true;
    this->id = id;
}

void ThreadClient::run() {

    char buffer[BUF_SIZE];
    ssize_t bytes_received = 0;

	if (this->id == 0) {
		Message m1("n",this->id);
		this->messages.push(m1);
	} else {
		Message m1("j",this->id);
		this->messages.push(m1);		
	}

    while (keep_running){
        try {
	
			//recibir datos por socket
            
            usleep(id * 1000000 + 1000000); //removeme
            
            Message m("w",this->id); //removeme
            
            this->messages.push(m);
            
            //Message m("w",this->id); //removeme
            
            this->messages.push(m);
            
            //Message m("w",this->id); //removeme
            
            this->messages.push(m);

			keep_running = false;

        } catch (...) {
            if (!keep_running) break;
        } 
    }
    //shutdown(peer->get_fd(), SHUT_WR);
    //dead = true; 
    
	Message m2("e",this->id); //removeme
	
	this->messages.push(m2);    
    
    
}


ThreadClient:: ~ThreadClient(){

}
