#include <iostream>

#include "ServerConnection.h"
#include "../common_src/ClientMessage.h"
#include "../common_src/ClientGameStatusElements.h"

ServerConnection::ServerConnection(std::string host, std::string service) {
	if (!this->socket.socket_connect(host.c_str(), service.c_str()))
		throw ServerConnectionError("Failed to connect");

	char buffer;
	socket.socket_receive(&buffer, sizeof(char));

	this->client_id = buffer;
	this->receiving = true; 
	/* Habría que revisar si está bien este valor, es decir, si el primer turno
		 para usar el socket realmente debería ser un receive y no un send.		 */
}

ServerConnection::~ServerConnection() { }

MessageType ServerConnection::receiveIncomingEvent(){
	std::unique_lock<std::mutex> lock(this->mutex);
	MessageType message_type;
	this->socket.socket_receive((char*)&message_type, sizeof(MessageType));
	
	return message_type;
}

std::vector<MapListItem> ServerConnection::fetchAvailableMaps() {
	std::unique_lock<std::mutex> lock(this->mutex);

	ClientMessage message { TYPE_SEND_MAPS_LIST, 0 };
	this->socket.socket_send((char*)&message, sizeof(ClientMessage));

	char buffer[sizeof(size_t)];
	socket.socket_receive(buffer, sizeof(size_t));
	size_t response_size = *((size_t*)buffer);
	size_t n_maps = response_size/sizeof(MapListItem);

	std::vector<MapListItem> maps;
	maps.reserve(n_maps);
	for (int i = 0; i < n_maps; i++) {
		MapListItem item;
		socket.socket_receive((char*)&item, sizeof(MapListItem));

		maps.push_back(item);
	}
	return maps;
}

std::vector<GameListItem> ServerConnection::fetchGameOptions() {
	std::unique_lock<std::mutex> lock(this->mutex);

	ClientMessage message { TYPE_REFRESH_GAMES_LIST, 0 };
	this->socket.socket_send((char*)&message, sizeof(ClientMessage));

	char buffer[sizeof(size_t)];
	this->socket.socket_receive(buffer, sizeof(size_t));
	size_t response_size = *((size_t*)buffer);
	size_t n_games = response_size/sizeof(GameListItem);

	std::vector<GameListItem> options;
	options.reserve(n_games);
	for (int i = 0; i < n_games; i++) {
		GameListItem item;
		socket.socket_receive((char*)&item, sizeof(GameListItem));

		options.push_back(item);
	}
	return options;
}

bool ServerConnection::joinGame(char game_id) {
	std::unique_lock<std::mutex> lock(this->mutex);

	ClientMessage message { TYPE_JOIN_GAME, game_id };
	this->socket.socket_send((char*)&message, sizeof(ClientMessage));

	char buffer;
	this->socket.socket_receive(&buffer, 1);

	return bool(buffer);
}

LobbyStatusData ServerConnection::fetchLobbyStatus() {
	std::unique_lock<std::mutex> lock(this->mutex);

	LobbyStatusData lobby_status;
	this->socket.socket_receive((char*)&lobby_status, sizeof(LobbyStatusData));

	return lobby_status;
}

void ServerConnection::exitLobby() {
	std::unique_lock<std::mutex> lock(this->mutex);

	ClientMessage message { TYPE_EXIT_GAME, 0 };
	this->socket.socket_send((char*)&message, sizeof(ClientMessage));
}

Map ServerConnection::fetchMap() {
	std::unique_lock<std::mutex> lock(this->mutex);

	/*
	MessageType message_type;
	this->socket.socket_receive((char*)&message_type, sizeof(MessageType));
	if (message_type != TYPE_SERVER_SEND_MAP) {
		throw ServerConnectionError("Expected map");
	} else {
		size_t map_data_size;
		this->socket.socket_receive((char*)&map_data_size, sizeof(size_t));

		char map_data[map_data_size];
		this->socket.socket_receive(map_data, map_data_size);		
	}
	*/

	size_t map_data_size;
	this->socket.socket_receive((char*)&map_data_size, sizeof(size_t));

	char map_data[map_data_size];
	this->socket.socket_receive(map_data, map_data_size);

	// TODO: Construir el mapa con la data y devolverlo
	Map map("../maps/map1.yml");
	return map;
}

void ServerConnection::sendEvents(std::vector<MessageType> events) {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (this->receiving) this->cv.wait(lock);

	if (events.size() == 0) {
		events.push_back(TYPE_CLIENT_PING);
	}

	size_t message_size = events.size()*sizeof(ClientMessage);
	this->socket.socket_send((char*)&message_size, sizeof(size_t));
	
	for (MessageType event : events) {
		ClientMessage message { event, 0 };
		this->socket.socket_send((char*)&message, sizeof(ClientMessage));
	}
	
	this->receiving = true;
	cv.notify_one();
}

void ServerConnection::sendPing() {
	std::unique_lock<std::mutex> lock(this->mutex);

	ClientMessage message { TYPE_CLIENT_PING, 0 };

	size_t message_size = sizeof(ClientMessage);
	this->socket.socket_send((char*)&message_size, sizeof(message_size));

	
	this->socket.socket_send((char*)&message, sizeof(message));
	
}

GameStatistics ServerConnection::receiveStatistics() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (this->receiving) this->cv.wait(lock);

	GameStatistics statistics;
	this->socket.socket_receive((char*)&statistics, sizeof(GameStatistics));

	this->receiving = false;
	cv.notify_one();
	return statistics;
}

GameStatusUpdate ServerConnection::fetchGameStatusUpdate() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->receiving) this->cv.wait(lock);

	/*
	MessageType message_type;
	this->socket.socket_receive((char*)&message_type, sizeof(MessageType));
	if (message_type != TYPE_SERVER_SEND_GAME_UPDATE) {
		throw ServerConnectionError("Expected game update");
	}*/ //USING RECEIVE INCOMNING EVENT

	PlayerStatus player_status;
	this->socket.socket_receive((char*)&player_status, sizeof(PlayerStatus));

	std::vector<PlayerListItem> players_list;
	size_t player_list_size;
	this->socket.socket_receive((char*)&player_list_size, sizeof(size_t));
	size_t n_players = player_list_size/sizeof(PlayerListItem);
	players_list.reserve(n_players);
	for (int i = 0; i < n_players; i++) {
		PlayerListItem player;

		this->socket.socket_receive((char*)&player, sizeof(PlayerListItem));
		if (player.clientId != this->client_id) players_list.push_back(player);
	}

	std::vector<DoorListItem> doors_list;
	size_t door_list_size;
	this->socket.socket_receive((char*)&door_list_size, sizeof(size_t));
	size_t n_doors = door_list_size/sizeof(DoorListItem);
	doors_list.reserve(n_doors);
	for (int i = 0; i < n_doors; i++) {
		DoorListItem door;

		this->socket.socket_receive((char*)&door, sizeof(DoorListItem));
		doors_list.push_back(door);
	}

	std::vector<ItemListElement> items_list;
	size_t item_list_size;
	this->socket.socket_receive((char*)&item_list_size, sizeof(size_t));
	size_t n_items = item_list_size/sizeof(ItemListElement);
	items_list.reserve(n_items);
	for (int i = 0; i < n_items; i++) {
		ItemListElement item;

		this->socket.socket_receive((char*)&item, sizeof(ItemListElement));
		items_list.push_back(item);
	}

	GameStatusUpdate update;
	update.position = player_status.position;
	update.direction = player_status.direction;
	update.enemies = players_list;

	this->receiving = false;
	cv.notify_one();
	return update;
}

ServerConnectionError::ServerConnectionError(const char *error) noexcept {
	snprintf(this->error_msg, ERROR_BUF_LEN, "Connection error: %s", error);
}

ServerConnectionError::~ServerConnectionError() { }

const char* ServerConnectionError::what() const noexcept {
  return this->error_msg;
}
