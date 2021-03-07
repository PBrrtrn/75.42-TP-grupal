#include <iostream>

#include "ServerConnection.h"
#include "../common_src/ClientMessage.h"
#include "../common_src/FiringState.h"
#include "../common_src/ClientGameStatusElements.h"

ServerConnection::ServerConnection(std::string host, std::string service) {
  if (!this->socket.socket_connect(host.c_str(), service.c_str()))
    throw ServerConnectionError("Failed to connect");

  char buffer;
  ssize_t receive = socket.socket_receive(&buffer, sizeof(char));
  if (receive < 0) throw ServerConnectionError("Failed to connect");

  this->client_id = buffer;
}

ServerConnection::~ServerConnection() { }

MessageType ServerConnection::receiveMessageType() {
  MessageType message_type;
  ssize_t receive = this->socket.socket_receive((char*)&message_type, sizeof(MessageType));
  if (receive < 0) throw ServerConnectionError("Failed to connect");
  
  return message_type;
}

std::vector<MapListItem> ServerConnection::getMapOptions() {
  char buffer[sizeof(size_t)];
  ssize_t receive = socket.socket_receive(buffer, sizeof(size_t));
  if (receive < 0) throw ServerConnectionError("Failed to connect");

  size_t response_size = *((size_t*)buffer);
  size_t n_maps = response_size/sizeof(MapListItem);

  std::vector<MapListItem> maps;
  maps.reserve(n_maps);
  for (int i = 0; i < n_maps; i++) {
    MapListItem item;
    ssize_t receive = socket.socket_receive((char*)&item, sizeof(MapListItem));
    if (receive < 0) throw ServerConnectionError("Failed to connect");

    maps.push_back(item);
  }

  return maps;
}

std::vector<GameListItem> ServerConnection::getGameOptions() {
  char buffer[sizeof(size_t)];
  ssize_t receive = this->socket.socket_receive(buffer, sizeof(size_t));
  if (receive < 0) throw ServerConnectionError("Failed to connect");

  size_t response_size = *((size_t*)buffer);
  size_t n_games = response_size/sizeof(GameListItem);

  std::vector<GameListItem> options;
  options.reserve(n_games);
  for (int i = 0; i < n_games; i++) {
    GameListItem item;
    ssize_t receive = socket.socket_receive((char*)&item, sizeof(GameListItem));
    if (receive < 0) throw ServerConnectionError("Failed to connect");

    options.push_back(item);
  }
  return options;
}

LobbyStatusData ServerConnection::getLobbyStatus() {
  LobbyStatusData lobby_status;
  ssize_t receive = this->socket.socket_receive((char*)&lobby_status, sizeof(LobbyStatusData));
  if (receive < 0) throw ServerConnectionError("Failed to connect");

  return lobby_status;
}

Map ServerConnection::getMap() {
  size_t map_data_size;
  int width;
  int height;
  this->socket.socket_receive((char*)&width, sizeof(int));
  this->socket.socket_receive((char*)&height, sizeof(int));

  int receive;
  receive = this->socket.socket_receive((char*)&map_data_size, sizeof(size_t));
  if (receive < 0) throw ServerConnectionError("Failed to connect");

  int* mapGrid = new int[width*height];
  this->socket.socket_receive((char*)mapGrid, map_data_size);
  Map map(width,height,mapGrid);
  delete mapGrid;
  
  return map;
}

GameStatusUpdate ServerConnection::getGameStatusUpdate() {
  int receive; 

  PlayerStatus player_status;
  receive = this->socket.socket_receive((char*)&player_status, sizeof(PlayerStatus));
  if (receive < 0) throw ServerConnectionError("Failed to connect");

  std::vector<PlayerListItem> players_list;
  size_t player_list_size;
  receive = this->socket.socket_receive((char*)&player_list_size, sizeof(size_t));
  if (receive < 0) throw ServerConnectionError("Failed to connect");
  size_t n_players = player_list_size/sizeof(PlayerListItem);
  players_list.reserve(n_players);
  for (int i = 0; i < n_players; i++) {
    PlayerListItem player;
    receive = this->socket.socket_receive((char*)&player, sizeof(PlayerListItem));
    if (receive < 0) throw ServerConnectionError("Failed to connect");

    if (player.clientId != this->client_id) players_list.push_back(player);
  }

  std::vector<DoorListItem> doors_list;
  size_t door_list_size;
  receive = this->socket.socket_receive((char*)&door_list_size, sizeof(size_t));
  if (receive < 0) throw ServerConnectionError("Failed to connect");
  size_t n_doors = door_list_size/sizeof(DoorListItem);
  doors_list.reserve(n_doors);
  for (int i = 0; i < n_doors; i++) {
    DoorListItem door;
    receive = this->socket.socket_receive((char*)&door, sizeof(DoorListItem));
    if (receive < 0) throw ServerConnectionError("Failed to connect");

    doors_list.push_back(door);
  }

  std::vector<ItemListElement> items_list;
  size_t item_list_size;
  receive = this->socket.socket_receive((char*)&item_list_size, sizeof(size_t));
  if (receive < 0) throw ServerConnectionError("Failed to connect");
  size_t n_items = item_list_size/sizeof(ItemListElement);
  items_list.reserve(n_items);
  for (int i = 0; i < n_items; i++) {
    ItemListElement item;
    receive = this->socket.socket_receive((char*)&item, sizeof(ItemListElement));
    if (receive < 0) throw ServerConnectionError("Failed to connect");

    items_list.push_back(item);
  }

  GameStatusUpdate update;

  update.position = player_status.position;
  update.direction = player_status.direction;
  update.health = player_status.health;
  update.selected_weapon = player_status.selectedWeapon;
  update.bullets = player_status.bullets;
  update.lives = player_status.lives;
  update.has_key = player_status.hasKey;
  update.player_firing = player_status.firing_state;
  update.enemies = players_list;
  update.items = items_list;
  // TODO: Guardar directamente sobre update

  return update;
}

GameStatistics ServerConnection::getGameStatistics() {
  GameStatistics statistics;
  ssize_t receive = this->socket.socket_receive((char*)&statistics, sizeof(GameStatistics));
  if (receive < 0) throw ServerConnectionError("Failed to connect");
  std::cout << "SOY CLIENTE RECIBI STATISTICS" << std::endl;
  return statistics;
}

void ServerConnection::sendMessage(ClientMessage message) {
  int send = this->socket.socket_send((char*)&message, sizeof(ClientMessage));
  if (send < 0) throw ServerConnectionError("Failed to connect");
}

ServerConnectionError::ServerConnectionError(const char *error) noexcept {
  snprintf(this->error_msg, ERROR_BUF_LEN, "Connection error: %s", error);
}

ServerConnectionError::~ServerConnectionError() { }

const char* ServerConnectionError::what() const noexcept {
  return this->error_msg;
}
