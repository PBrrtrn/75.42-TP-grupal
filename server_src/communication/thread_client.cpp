#include "thread_client.h"

ThreadClient::ThreadClient(int id, BlockingQueue<Message>& messages, 
	BlockingQueue<Message>* messagesOut, Socket&& socket, ServerStatus& serverStatus) : 
		id(id), messages(messages), messages_out(messagesOut), 
		peer(std::move(socket)), keep_running(true), 
		dead(false), serverStatus(serverStatus) {
}

void ThreadClient::run() {
    char buffer[BUF_SIZE];
    ssize_t bytes_received = 0;

	this->informClientId(); 
	this->sendGamesList(); //TODO removeme --> para pruebas con server_clienttest.cpp

	this->choosing_game = true;

	while(choosing_game){	
		this->peer.socket_receive(buffer, sizeof(char)*2);
		std::cout << "evento: "<< buffer[0] <<", mapId:"<< std::to_string(buffer[1]) << std::endl;
		Message m(buffer[0], buffer[1], this->id);
		this->messages.push(m);
		Message answer = this->messages_out->pop();
		char result_join;
		switch (answer.getType())
		{
		case TYPE_SERVER_JOIN_OK:
			this->choosing_game = false;
			result_join = 0;
			break;
		case TYPE_SERVER_JOIN_REFUSED:
			result_join = -1;
			break;
		default:
			break;
		}
		this->peer.socket_send(&result_join, sizeof(result_join)); 
	}

    while (keep_running){
        try {
	
			//recibir datos por socket
            
            //this->socket.receive(&datos,tamanioDeDatos); //recibo datos binarios
         
			//Message m = MessageParser.parse(datos,tamanioDeDatos); //convierto datos binarios a un message.
            
            //usleep(id * 1000000 + 1000000); //removeme
            
            //Message m(TYPE_MOVE_FORWARD,0,0,this->id); //removeme
            
            //this->messages.push(m);

			if ( this->messages_out != NULL && !this->messages_out->isEmpty()) 
			//puede que haya un problema similar al de la cola de entrada al servidor - 
			//hay que bloquear la cola, desencolar TODOS los game status pendientes de envio, 
			//y luego desbloquear
			{
				Message m = this->messages_out->pop();
				std::cout << "got a new event in outgoing queue in client " << this->id << 
					" of type: " << m.getType() << std::endl; 
				switch (m.getType())
				{
				case TYPE_SERVER_SEND_GAMES_LIST:
					this->sendGamesList();
					break;
				case TYPE_SERVER_SEND_MAP_LIST:
					break;
				case TYPE_SERVER_SEND_MAP:
					break;
				case TYPE_SERVER_SEND_GAME_UPDATE:
					break;
				default:
					break;
				}
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

void ThreadClient::assignToOutQueue(BlockingQueue<Message>* messages_out){
	this->messages_out = messages_out;
}

void ThreadClient::informClientId() {
	char client_id = (char)this->id;
    this->peer.socket_send(&client_id, sizeof(client_id));
}

void ThreadClient::sendGamesList() {
	std::vector<GameListItem> list = this->serverStatus.getGamesList();
	char size = list.size()*sizeof(GameListItem);
	this->peer.socket_send(&size, sizeof(char));
	for (auto& it: list) {
		this->peer.socket_send((char*)(&it), sizeof(GameListItem));
	}
}

void ThreadClient::shutdown(){
	this->keep_running = false;
	this->choosing_game = false;
}

ThreadClient:: ~ThreadClient(){}
