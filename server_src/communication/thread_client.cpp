#include "thread_client.h"

ThreadClient::ThreadClient(int id, BlockingQueue<Message>* messagesOut, 
	Socket& socket, ServerStatus& serverStatus, LobbyStatus& lobbyStatus) : 
		id(id),
		messages_out(messagesOut), 
		peer(socket), 
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

	if(!this->informClientId()) this->shutdown(); 

	this->choosing_game = true;

	while(choosing_game){
		try{
			Message answer = this->messages_out->pop();
			if(!this->informSomethingToReport(answer.getType())) this->shutdown();
			switch (answer.getType())
			{
			case TYPE_SERVER_SEND_GAMES_LIST:
				if (!this->sendGamesList()) this->shutdown();
				break;			
			case TYPE_SERVER_JOIN_OK:
				this->choosing_game = false;
				//this->sendJoinOk();
				break;
			case TYPE_SERVER_JOIN_REFUSED:
				if (!this->sendJoinRefused()) this->shutdown();
				break;
			case TYPE_SERVER_SEND_MAP_LIST:
				if(!this->sendMapsList()) this->shutdown();
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

	std::cout << "ThreadClient "<< this->id <<": voy a ingresar loop de juego" << std::endl;

    while (keep_running){
        try {
			Message m = this->messages_out->pop();
			if(!this->informSomethingToReport(m.getType())) this->shutdown();
			switch (m.getType())
			{
			case TYPE_SERVER_SEND_MAP:
				if(!this->sendCurrentGameMap()) this->shutdown();
				break;					
			case TYPE_LOBBY_STATUS_UPDATE:
				if (!this->sendLobbyStatus(m.getEntity())) this->shutdown();
				break;
			case TYPE_SERVER_SEND_GAME_UPDATE:
				if (!this->sendGameUpdate()) this->shutdown();
				break;
			case TYPE_SERVER_SEND_GAME_STATISTICS:
				if (!this->sendGameStatistics()) this->shutdown();
				break;
			default:
				//std::cout << "ThreadClient "<< this->id <<": no se donde estoy! no procese este evento!" << std::endl;
				break;
			}
			
        } catch (...) {
            //if (!keep_running) break;
			this->shutdown();
        }
    }
}

bool ThreadClient::informNothingToReport(){
	MessageType message = TYPE_SERVER_NOTHING_TO_REPORT;
	int send = this->peer.socket_send((char*)&message, sizeof(MessageType));
	if (send < 0) return false;
	return true;
}

bool ThreadClient::informSomethingToReport(MessageType type){
	MessageType message = type;
	int send = this->peer.socket_send((char*)&message, sizeof(MessageType));
	if (send < 0) return false;
	return true;
}


bool ThreadClient::sendCurrentGameMap(){
	int send;
	int* mapGrid = this->game_status->getMapGrid();
	size_t size = this->game_status->getMapWidth() * this->game_status->getMapHeight() * sizeof(int);

	int width = this->game_status->getMapWidth();
	int height = this->game_status->getMapHeight();

	std::cout << "Map width:" << std::to_string(size) << std::endl;
	std::cout << "Map height:" << std::to_string(size) << std::endl;
	std::cout << "Map size:" << std::to_string(size) << std::endl;
	send = this->peer.socket_send((char*)(&width), sizeof(width));
	if (send < 0) return false;
	send = this->peer.socket_send((char*)(&height), sizeof(height));
	if (send < 0) return false;
	send = this->peer.socket_send((char*)(&size), sizeof(size));
	if (send < 0) return false;
	send = this->peer.socket_send((char*)mapGrid,size);
	if (send < 0) return false;

	std::cout << "Map sent" << std::endl;

	delete[] mapGrid;

	std::cout << "Map grid data released - pointer deleted" << std::endl;
	return true;
}

bool ThreadClient::sendGameUpdate() {
	int send;
	if (this->game_status == NULL) {
		std::cout << "gameStatus pointer in client is NULL!" << std::endl;
		return false;
	}
	send = this->peer.socket_send((char*)(&this->game_status->thisPlayerStatus), sizeof(PlayerStatus));
	if (send < 0) return false;

	size_t size = this->game_status->players.size()*sizeof(PlayerListItem);
	send = this->peer.socket_send((char*)(&size), sizeof(size));
	if (send < 0) return false;
	for (auto& it: this->game_status->players) {
		send = this->peer.socket_send((char*)&(it.second), sizeof(PlayerListItem));
		if (send < 0) return false;
	}

	//char door_
	size = this->game_status->doors.size()*sizeof(DoorListItem);
	send = this->peer.socket_send((char*)(&size), sizeof(size));
	if (send < 0) return false;
	for (auto& it: this->game_status->doors) {
		send = this->peer.socket_send((char*)(&it.second), sizeof(DoorListItem));
		if (send < 0) return false;
	}

	size = this->game_status->items.size()*sizeof(ItemListElement);
	send = this->peer.socket_send((char*)(&size), sizeof(size));
	if (send < 0) return false;
	for (auto& it: this->game_status->items) {
		send = this->peer.socket_send((char*)(&it), sizeof(ItemListElement));
		if (send < 0) return false;
	}
	return true;
}

void ThreadClient::assignToOutQueue(BlockingQueue<Message>* messages_out){
	this->messages_out = messages_out;
}

void ThreadClient::assignToGameStatus(ClientGameStatus* gs){
	this->game_status = gs;
}

bool ThreadClient::informClientId() {
	char client_id = (char)this->id;
    int send = this->peer.socket_send(&client_id, sizeof(client_id));
	if (send < 0) return false;
	
	std::cout << "Client ID sent" << std::endl;
	return true;
}

bool ThreadClient::sendGamesList() {
	std::vector<GameListItem> list = this->serverStatus.getGamesList();
	size_t size = list.size()*sizeof(GameListItem);
	int send = this->peer.socket_send((char*)(&size), sizeof(size_t));
	if (send < 0) return false;
	for (auto& it: list) {
		send = this->peer.socket_send((char*)(&it), sizeof(GameListItem));
		if (send < 0) return false;
	}
	return true;
}

bool ThreadClient::sendLobbyStatus(int gameID) {
	LobbyStatusData lobbyStatus = this->lobbyStatus.getLobbyStatus(gameID);
	int send = this->peer.socket_send((char*)(&lobbyStatus), sizeof(LobbyStatusData));
	if (send < 0) return false;
	this->game_started = lobbyStatus.gameStarted;
	return true;
}

bool ThreadClient::sendGameStatistics() {
	GameStatistics gs = this->game_status->getStatistics();
	int send = this->peer.socket_send((char*)(&gs), sizeof(GameStatistics));
	if (send < 0) return false;
	return true;
}

bool ThreadClient::sendMapsList() {
	int send;
	std::cout << "Sending maps list" << std::endl;
	const std::vector<MapListItem>& list = this->serverStatus.getMapsList();
	size_t size = list.size()*sizeof(MapListItem);
	send = this->peer.socket_send((char*)(&size), sizeof(size));
	if (send < 0) return false;
	for (auto& it: list) {
		send = this->peer.socket_send((char*)(&it), sizeof(MapListItem));
		if (send < 0) return false;
	}
	return true;
}

bool ThreadClient::sendJoinOk() {
	char result_join = 0;
	int send = this->peer.socket_send(&result_join, sizeof(result_join)); 
	if (send < 0) return false;

	std::cout << "Join OK sent" << std::endl;
	return true;
}

bool ThreadClient::sendJoinRefused() {
	char result_join = -1;
	int send = this->peer.socket_send(&result_join, sizeof(result_join)); 
	if (send < 0) return false;
	return true;
}

void ThreadClient::shutdown(){
	this->keep_running = false;
	this->choosing_game = false;
	this->messages_out->close();
}

ThreadClient:: ~ThreadClient(){	
	delete this->messages_out;
}
