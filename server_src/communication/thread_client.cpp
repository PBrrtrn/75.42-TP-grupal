#include "thread_client.h"

ThreadClient::ThreadClient(int id, BlockingQueue<Message>* messagesOut, 
	Socket&& socket, ServerStatus& serverStatus, LobbyStatus& lobbyStatus) : 
		id(id),
		messages_out(messagesOut), 
		peer(std::move(socket)), 
		keep_running(true), 
		dead(false), 
		serverStatus(serverStatus), 
		lobbyStatus(lobbyStatus) 
		{
			this->game_status = NULL;
			this->game_started = false;
}

void ThreadClient::run() {
    char buffer[BUF_SIZE];

	this->informClientId(); 

	this->choosing_game = true;

	while(choosing_game){
		ClientMessage cMessage;
		size_t received = this->peer.socket_receive((char*)(&cMessage), sizeof(cMessage));
		if (received < sizeof(cMessage)){
			std::cout << "recv en threadclient fallo, no recibi nada! (cerro el socket?)" << std::endl;
			this->shutdown();
		} else {
			Message m(cMessage.type, cMessage.entityId, this->id);
			this->messages.push(m);
			try{
				Message answer = this->messages_out->pop();
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

	std::cout << "ThreadClient "<< this->id <<": voy a ingresar loop de juego" << std::endl;

    while (keep_running){
        try {
			Message m = this->messages_out->pop();
			this->informSomethingToReport(m.getType());
			switch (m.getType())
			{
			case TYPE_SERVER_SEND_MAP:
				std::cout << "ThreadClient "<< this->id <<": voy a enviar mapa" << std::endl;
				this->sendCurrentGameMap();
				break;					
			case TYPE_LOBBY_STATUS_UPDATE:
				this->sendLobbyStatus(m.getEntity());
				break;
			case TYPE_SERVER_SEND_GAME_UPDATE:
				this->sendGameUpdate();
				break;
			case TYPE_SERVER_SEND_GAME_STATISTICS:
				std::cout << "ThreadClient "<< this->id <<": voy a mandar statistics" << std::endl;
				this->sendGameStatistics();
				break;
			default:
				std::cout << "ThreadClient "<< this->id <<": no se donde estoy! no procese este evento!" << std::endl;
				break;
			}
			
        } catch (...) {
            if (!keep_running) break;
        }
    }
}

void ThreadClient::informNothingToReport(){
	MessageType message = TYPE_SERVER_NOTHING_TO_REPORT;
	this->peer.socket_send((char*)&message, sizeof(MessageType));
}

void ThreadClient::informSomethingToReport(MessageType type){
	MessageType message = type;
	this->peer.socket_send((char*)&message, sizeof(MessageType));
}


void ThreadClient::sendCurrentGameMap(){
   std::string mapa = this->game_status->getEntireMap();
   size_t size = mapa.length() + 1;
   
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

	size_t size = this->game_status->players.size()*sizeof(PlayerListItem);
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
    
    std::cout << "client id enviado" << std::endl;
    
}

void ThreadClient::sendGamesList() {
	std::vector<GameListItem> list = this->serverStatus.getGamesList();
	size_t size = list.size()*sizeof(GameListItem);
	this->peer.socket_send((char*)(&size), sizeof(size_t));
	for (auto& it: list) {
		this->peer.socket_send((char*)(&it), sizeof(GameListItem));
	}
}

void ThreadClient::sendLobbyStatus(int gameID) {
	LobbyStatusData lobbyStatus = this->lobbyStatus.getLobbyStatus(gameID);
	this->peer.socket_send((char*)(&lobbyStatus), sizeof(LobbyStatusData));
	this->game_started = lobbyStatus.gameStarted;
}

void ThreadClient::sendGameStatistics() {
	GameStatistics gs = this->game_status->getStatistics();
	this->peer.socket_send((char*)(&gs), sizeof(GameStatistics));
}

void ThreadClient::sendMapsList() {
	const std::vector<MapListItem>& list = this->serverStatus.getMapsList();
	size_t size = list.size()*sizeof(MapListItem);
	this->peer.socket_send((char*)(&size), sizeof(size));
	for (auto& it: list) {
		this->peer.socket_send((char*)(&it), sizeof(MapListItem));
	}
}

void ThreadClient::sendJoinOk() {
	char result_join = 0;
	this->peer.socket_send(&result_join, sizeof(result_join)); 
	
	std::cout << "join OK enviado" << std::endl;
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
