#include "thread_client.h"

ThreadClient::ThreadClient(int id, BlockingQueue<Message>& messages, BlockingQueue<Message>* messagesOut, Socket&& socket) : 
		id(id), messages(messages) , messages_out(messagesOut), peer(std::move(socket)), keep_running(true), dead(false) {
    //this->keep_running = true;
    //this->id = id;
    //this->messages_out = messagesOut;
}

void ThreadClient::run() {

    char buffer[BUF_SIZE];
    ssize_t bytes_received = 0;
    
    
    
    std::cout << "string:"<< std::to_string(id) << std::endl;
    
    char client_id = (char)id;
    
    this->peer.socket_send(&client_id, sizeof(client_id));

	//if (this->id == 0) {
	//	Message m1(TYPE_START_GAME,0,0,this->id);
	//	this->messages.push(m1);
	//} else {
    //    usleep(3000000);
	//	Message m1(TYPE_JOIN_GAME,0,0,this->id);
	//	this->messages.push(m1);		
	//}

    while (keep_running){
        try {
	
			//recibir datos por socket
            
            //this->socket.receive(&datos,tamanioDeDatos); //recibo datos binarios
         
			//Message m = MessageParser.parse(datos,tamanioDeDatos); //convierto datos binarios a un message.
            
            //usleep(id * 1000000 + 1000000); //removeme
            
            //Message m(TYPE_MOVE_FORWARD,0,0,this->id); //removeme
            
            //this->messages.push(m);

			if ( this->messages_out != NULL && !this->messages_out->isEmpty()) //puede que haya un problema similar al de la cola de entrada al servidor - hay que bloquear la cola, desencolar TODOS los game status pendientes de envio, y luego desbloquear
			{
				this->messages_out->pop();
				std::cout << "got a new event in outgoing queue in client " << this->id << std::endl; 
				//switch evento.getType(){
					// si hay que enviar gameList..
					// si hay que enviar mapList..
					// si hay que enviar Map..
					// si hay que enviar ClientGameStatus..
				//}
			}

        } catch (...) {
            if (!keep_running) break;
        } 
    }
    //shutdown(peer->get_fd(), SHUT_WR);
    //dead = true; 
    
	//Message m2(TYPE_EXIT_GAME,0,0,this->id); //removeme
	
	//this->messages.push(m2);    
    
    
}

//void ThreadClient::assignToOutQueue(BlockingQueue<Message>* messages_out){
//	this->messages_out = messages_out;
//}

ThreadClient:: ~ThreadClient(){}
