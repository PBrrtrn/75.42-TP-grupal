#include "thread_client.h"

ThreadClient::ThreadClient(int id, BlockingQueue<Message>& messages, 
	BlockingQueue<Message>* messagesOut, Socket&& socket, ServerStatus& serverStatus, 
	LobbyStatus& lobbyStatus) : 
		id(id), messages(messages), messages_out(messagesOut), 
		peer(std::move(socket)), keep_running(true), 
		dead(false), serverStatus(serverStatus), lobbyStatus(lobbyStatus) {
			this->game_status = NULL;
}

void ThreadClient::run() {
    char buffer[BUF_SIZE];
    ssize_t bytes_received = 0;

	this->informClientId(); 
	this->sendGamesList(); //TODO removeme --> para pruebas con server_clienttest.cpp

	this->choosing_game = true;

	while(choosing_game){	
		int received = this->peer.socket_receive(buffer, sizeof(char)*2);
		//std::cout <<  "received:" << received << std::endl ;
		if (received < sizeof(char)*2){
			std::cout << "recv en threadclient fallo, no recibi nada! (cerro el socket?)" << std::endl;
			this->shutdown();
		} else {
			//std::cout << "evento: "<< buffer[0] <<", mapId o gameId:" 
			//	<< std::to_string(buffer[1]) << std::endl;
			Message m(buffer[0], buffer[1], this->id);
			this->messages.push(m);
			try{
				Message answer = this->messages_out->pop();
				//char result_join;
				switch (answer.getType())
				{
				case TYPE_SERVER_SEND_GAMES_LIST:
					this->sendGamesList();
					break;			
				case TYPE_SERVER_JOIN_OK:
					this->choosing_game = false;
					this->sendJoinOk();
					break;
				case TYPE_SERVER_JOIN_REFUSED:
					this->sendJoinRefused();
					break;
				case TYPE_SERVER_SEND_MAP_LIST:
					this->sendMapsList();
					break;

				case TYPE_SERVER_SHUTDOWN_CLIENT:
					this->shutdown();
					break;				
				default:
					break;
				}			
			} catch (...) {
				this->shutdown();
			}
		}

	} 

	std::cout << "ThreadClient: voy a ingresar loop de juego" << std::endl;

    while (keep_running){
        try {

			if ( this->messages_out != NULL && !this->messages_out->isEmpty()) 
			//puede que haya un problema similar al de la cola de entrada al servidor - 
			//hay que bloquear la cola, desencolar TODOS los game status pendientes de envio, 
			//y luego desbloquear
			{
				Message m = this->messages_out->pop();
				this->informSomethingToReport();
				//std::cout << "got a new event in outgoing queue in client " << this->id << 
				//	" of type: " << m.getType() << std::endl; 
				switch (m.getType())
				{
				case TYPE_SERVER_SEND_MAP:
					this->sendCurrentGameMap();
					break;					
				case TYPE_LOBBY_STATUS_UPDATE:
					this->sendLobbyStatus(m.getEntity());
					break;
				case TYPE_SERVER_SEND_GAME_UPDATE:
					this->sendGameUpdate();
					break;
				case TYPE_SERVER_SEND_GAME_STATISTICS:
					break;
				default:
					break;
				}
			} else {
				this->informNothingToReport();
			}
			
			std::cout << "Escuchando eventos de cliente remoto o ping" << std::endl;
			
			int received = this->peer.socket_receive(buffer, sizeof(char)*2);
			if (received < sizeof(char)*2){
				std::cout << "recv en threadclient fallo, no recibi nada! (cerro el socket?)" << std::endl;
				this->shutdown();
			} else {
				Message m(buffer[0], buffer[1], this->id);
				this->messages.push(m);				
			}
			

			
			

        } catch (...) {
            if (!keep_running) break;
        }
        
        
         
    }
}

void ThreadClient::informNothingToReport(){
	char message = 0;
	std::cout << "informando que no hay nada que reportar" << std::endl;
	this->peer.socket_send(&message, sizeof(char));
}

void ThreadClient::informSomethingToReport(){
	char message = 1;
	std::cout << "informando que hay algo que reportar" << std::endl;
	this->peer.socket_send(&message, sizeof(char));
}


void ThreadClient::sendCurrentGameMap(){
   std::string mapa = this->game_status->getEntireMap();
   int size = mapa.length() + 1;
   
   std::cout << "tamanio del mapa:" << std::to_string(size) << std::endl;
   
   this->peer.socket_send((char*)(&size), sizeof(size));
   this->peer.socket_send(mapa.c_str(), size - 1);
   char endOfFile = 0;
   this->peer.socket_send((&endOfFile), sizeof(char));
}

void ThreadClient::sendGameUpdate() {
	if (this->game_status == NULL) {
		std::cout << "gameStatus pointer in client is NULL!" << std::endl;
		return;
	}
	this->peer.socket_send((char*)(&this->game_status->thisPlayerStatus), sizeof(PlayerStatus));

	int size = this->game_status->players.size()*sizeof(PlayerListItem);
	this->peer.socket_send((char*)(&size), sizeof(size));
	for (auto& it: this->game_status->players) {
		this->peer.socket_send((char*)(&it), sizeof(PlayerListItem));
	}

	//char door_
	size = this->game_status->doors.size()*sizeof(DoorListItem);
	this->peer.socket_send((char*)(&size), sizeof(size));
	for (auto& it: this->game_status->doors) {
		this->peer.socket_send((char*)(&it), sizeof(DoorListItem));
	}

	//char item_
	size = this->game_status->items.size()*sizeof(ItemListElement);
	this->peer.socket_send((char*)(&size), sizeof(size));
	for (auto& it: this->game_status->items) {
		this->peer.socket_send((char*)(&it), sizeof(ItemListElement));
	}
}

void ThreadClient::assignToOutQueue(BlockingQueue<Message>* messages_out){
	this->messages_out = messages_out;
}

void ThreadClient::assignToGameStatus(ClientGameStatus* gs){
	this->game_status = gs;
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

void ThreadClient::sendLobbyStatus(int gameID) {
	LobbyStatusData lobbyStatus = this->lobbyStatus.getLobbyStatus(gameID);
	this->peer.socket_send((char*)(&lobbyStatus), sizeof(LobbyStatusData));
}

void ThreadClient::sendGameStatistics(int gameID) {
	GameStatistics gs = this->game_status->getStatistics();
	this->peer.socket_send((char*)(&gs), sizeof(GameStatistics));
}

void ThreadClient::sendMapsList() {
	//TODO chequear valgrind
	const std::vector<MapListItem>& list = this->serverStatus.getMapsList();
	char size = list.size()*sizeof(MapListItem);
	this->peer.socket_send(&size, sizeof(char));
	for (auto& it: list) {
		this->peer.socket_send((char*)(&it), sizeof(MapListItem));
	}
}

void ThreadClient::sendJoinOk() {
	char result_join = 0;
	this->peer.socket_send(&result_join, sizeof(result_join)); 
}

void ThreadClient::sendJoinRefused() {
	char result_join = -1;
	this->peer.socket_send(&result_join, sizeof(result_join)); 
}

void ThreadClient::shutdown(){
	this->keep_running = false;
	this->choosing_game = false;
	this->peer.close_socket();
	this->messages_out->close();
}

ThreadClient:: ~ThreadClient(){	}
