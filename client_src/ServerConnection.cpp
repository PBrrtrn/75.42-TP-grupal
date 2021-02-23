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
}

ServerConnection::~ServerConnection() { }

MessageType ServerConnection::receiveMessageType() {
	MessageType message_type;
	this->socket.socket_receive((char*)&message_type, sizeof(MessageType));
	
	return message_type;
}

std::vector<MapListItem> ServerConnection::getMapOptions() {
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

std::vector<GameListItem> ServerConnection::getGameOptions() {
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

LobbyStatusData ServerConnection::getLobbyStatus() {
	LobbyStatusData lobby_status;
	this->socket.socket_receive((char*)&lobby_status, sizeof(LobbyStatusData));

	return lobby_status;
}

Map ServerConnection::getMap() {
	size_t map_data_size;
	this->socket.socket_receive((char*)&map_data_size, sizeof(size_t));

	char map_data[map_data_size];
	this->socket.socket_receive(map_data, map_data_size);

	// TODO: Construir el mapa con la data y devolverlo
	Map map("../maps/map1.yml");
	return map;
}

GameStatusUpdate ServerConnection::getGameStatusUpdate() {
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

	return update;
}

GameStatistics ServerConnection::getGameStatistics() {
	GameStatistics statistics;
	this->socket.socket_receive((char*)&statistics, sizeof(GameStatistics));
	std::cout << "SOY CLIENTE RECIBI STATISTICS" << std::endl;
	return statistics;
}

void ServerConnection::sendMessage(ClientMessage message) {
	this->socket.socket_send((char*)&message, sizeof(ClientMessage));
}

ServerConnectionError::ServerConnectionError(const char *error) noexcept {
	snprintf(this->error_msg, ERROR_BUF_LEN, "Connection error: %s", error);
}

ServerConnectionError::~ServerConnectionError() { }

const char* ServerConnectionError::what() const noexcept {
  return this->error_msg;
}
