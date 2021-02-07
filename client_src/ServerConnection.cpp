#include <iostream>
#include "ServerConnection.h"

ServerConnection::ServerConnection(std::string host, std::string service) {
	if (!this->socket.socket_connect(host.c_str(), service.c_str())) {
		throw ServerConnectionError("Failed to connect");
	} else {
		char buffer[1];
		socket.socket_receive(buffer, sizeof(char));

		this->client_id = int(buffer[0]);
		std::cout << client_id << std::endl;
	}
}


ServerConnection::~ServerConnection() { }

std::vector<MapItem> ServerConnection::fetchAvailableMaps() {
	std::unique_lock<std::mutex> lock(this->mutex);
	/* Enviar un MessageType TYPE_SEND_MAP_LIST
		 Se va a recibir un header de tipo int/uint con el número de bytes
		 que se van a recibir. El número de items es nBytes/sizeof(MapListItem)

		 Luego del header se recibe una cierta cantidad de structs MapListItem
	*/
}

std::vector<GameOption> ServerConnection::fetchGameOptions() {
	std::unique_lock<std::mutex> lock(this->mutex);
	/* Enviar un MessageType TYPE_SEND_GAME_LIST
		 Se va a recibir un header de tipo int/uint con el número de bytes
		 que se van a recibir. El número de items es nBytes/sizeof(GameListItem)

		 Luego del header se recibe una cierta cantidad de structs GameListItem
	*/

	std::vector<GameOption> options;
	GameOption game_option { std::string("Mapin el mapa"), 4, 1 };
	options.push_back(game_option);

	return options;
}

bool ServerConnection::joinGame(int game_id) {
	/* 
		Enviar un MessageType TYPE_JOIN_GAME seguido del id del juego al que 
		quiero que me agreguen.
		Voy a recibir un bool que me indica si se pudo agregarme a la partida.
	*/
}

LobbyStatus ServerConnection::fetchLobbyStatus() {
	/*
		Recibe un mensaje del servidor con un LobbyStatusData.
		Una vez que joinGame resulta exitoso (devuelve true), se va a recibir
		un lobbyStatus desde el lado del MenuStatusUpdater hasta que pase una de
		dos cosas:
			* El cliente envíe un mensaje ExitLobby en cuyo caso se vuelve al menu
			* Se recibe un LobbyStatusData con el campo game_started en true, en cuyo
			caso se debe inicializar el juego
	*/
}

void ServerConnection::exitLobby() {
	// Se envia un MessageType TYPE_EXIT_GAME
}

Map ServerConnection::fetchMap() {
	/* Se recibe un header con el tamaño en bytes del archivo YML, seguido
	de la data del archivo. Debe castearse el YML a un YAML::Node y pasarse
	al constructor de Map y devolver el mapa.														 */
}

void ServerConnection::sendEvents() {
	
}

GameStatusUpdate ServerConnection::fetchGameStatusUpdate() {
	/* Se recibe un struct PlayerStatus.
	Luego se recibe un header int con el	número de bytes en la lista de 
	jugadores que se enviará, seguido de un número de structs PlayerListItem.
	Luego se recibe un header int con el número de bytes en la lista de puertas a
	recibir, seguido de un número de structs DoorListItem.
	Luego se recibe un header int con el número de bytes en la lista de items a
	recibir, seguiro de un número de structs ItemListElement									 */
}

ServerConnectionError::ServerConnectionError(const char *error) noexcept {
	snprintf(this->error_msg, ERROR_BUF_LEN, "Connection error: %s", error);
}

ServerConnectionError::~ServerConnectionError() { }

const char* ServerConnectionError::what() const noexcept {
  return this->error_msg;
}
