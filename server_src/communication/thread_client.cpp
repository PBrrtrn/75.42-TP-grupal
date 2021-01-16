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

	//if (this->id == 0) {
	if (true) {
		Message m1(TYPE_START_GAME,0,0,this->id);
		this->messages.push(m1);
	} else {
		Message m1(TYPE_JOIN_GAME,0,0,this->id);
		this->messages.push(m1);		
	}

    while (keep_running){
        try {
	
			//recibir datos por socket
            
            usleep(id * 1000000 + 1000000); //removeme
            
            Message m(TYPE_MOVE_FORWARD,0,0,this->id); //removeme
            
            this->messages.push(m);
            
            usleep(id * 1000000 + 1000000); //removeme
            
            //Message m("w",this->id); //removeme
            
            this->messages.push(m);
            
            usleep(id * 1000000 + 1000000); //removeme
            
            //Message m("w",this->id); //removeme
            
            this->messages.push(m);

			keep_running = false;

        } catch (...) {
            if (!keep_running) break;
        } 
    }
    //shutdown(peer->get_fd(), SHUT_WR);
    //dead = true; 
    
	Message m2(TYPE_EXIT_GAME,0,0,this->id); //removeme
	
	this->messages.push(m2);    
    
    
}


ThreadClient:: ~ThreadClient(){

}
