#include <iostream>
#include <unistd.h>

#include "../common_src/Socket.h"
#include "../common_src/GameListItem.h"
#include "../common_src/MapListItem.h"
#include "./communication/message.h"
#include "../common_src/LobbyStatusData.h"
#include "../common_src/ClientMessage.h"
#include "./games/client_game_status.h"

#define BUF_SIZE 64

void connectAndGetClientId(Socket& socket){
	char buffer[BUF_SIZE];
	bool resultado = socket.socket_connect("localhost","9006");
	size_t length = sizeof(char);
	//recibo el clientId
	socket.socket_receive(buffer,length);
	std::string clientId = std::to_string(buffer[0]);
	std::cout << "client id:" << clientId << std::endl;
	
}

void getAndPrintGameList(Socket& socket){
	//char buffer[BUF_SIZE];
	//size_t length = 1;
	//recibo el size del game list	
	size_t size;
	socket.socket_receive((char*)(&size),sizeof(size));
	//buffer[length] = '\0';	
	std::string gameListSize = std::to_string(size);
	std::cout << "size of game list:" << gameListSize << std::endl;	
	
	GameListItem list_item;
	
	std::cout << "iterations:" << size/sizeof(GameListItem) << std::endl;
	
	for (int i = 0; i < size/sizeof(GameListItem); i++ ){
		std::cout << "receiving game in list" << std::endl;
		socket.socket_receive((char*)(&list_item),sizeof(GameListItem));
		std::cout << "game index:" << i << ", gameId:" <<  std::to_string(list_item.gameId) << ",players:" << std::to_string(list_item.players)<< ",maxPlayers:" << std::to_string(list_item.maxPlayers)<< ",mapId:" << std::to_string(list_item.mapId) << std::endl;	
	}	
}

void getAndPrintMapList(Socket& socket){
	//char buffer[BUF_SIZE];
	//int length = 1;

	size_t size;
	//size_t length;

	socket.socket_receive((char*)(&size),sizeof(size));
	//buffer[length] = '\0';	
	std::string MapListSize = std::to_string(size);
	std::cout << "size of map list:" << MapListSize << std::endl;	
	
	MapListItem list_item;
	
	std::cout << "iterations:" << size/sizeof(MapListItem) << std::endl;
	
	for (int i = 0; i < size/sizeof(MapListItem); i++ ){
		std::cout << "receiving maps in list" << std::endl;
		socket.socket_receive((char*)(&list_item),sizeof(MapListItem));
		std::cout << "map index:" << i << ", map id:" <<  std::to_string(list_item.mapId) 
			<< ",players:" << std::to_string(list_item.minPlayers)<< 
			",maxPlayers:" << std::to_string(list_item.maxPlayers)<< 
			", map name:" << std::string(list_item.name) << std::endl;	
	}	
}

void askForGameList(Socket& socket){	
	ClientMessage m;
	
	m.type = CLIENT_REQUEST_GAMES_LIST;
	m.entityId = 0;
	
	socket.socket_send((char*)(&m),sizeof(m));
}

void askForMapList(Socket& socket){	
	ClientMessage m;
	
	m.type = CLIENT_REQUEST_MAPS_LIST;
	m.entityId = 0;
	
	socket.socket_send((char*)(&m),sizeof(m));	
	
}

void joinOrStartGame(Socket& socket,MessageType caracter,char mapOrGameId) {
char buffer[BUF_SIZE];			
int length;
//buffer[0] = caracter;
//buffer[1] = mapOrGameId;
//length = 2;

ClientMessage m;

m.type = caracter;
m.entityId = mapOrGameId;

//envio el evento join game, ej: j 3
if (caracter == CLIENT_REQUEST_JOIN_GAME)
	std::cout << "send join game" << std::endl;	
if (caracter == CLIENT_REQUEST_CREATE_GAME)
	std::cout << "send start game" << std::endl;	
//socket.socket_send(buffer,length);
socket.socket_send((char*)(&m),sizeof(m));	
length = 1;
std::cout << "receive join confirmation" << std::endl;	
socket.socket_receive(buffer,length);
if (buffer[0] == 0) {
	std::cout << "join successful" << std::endl;
	
	LobbyStatusData ls;
	ls.gameStarted = false;
	//char clientEvent[2];
	//clientEvent[0] = TYPE_CLIENT_PING;
	//clientEvent[1] = 0;
	MessageType report;				
	bool gameStarted = false;
	while(true) {
		//MessageType report;
		socket.socket_receive((char*)&report, sizeof(report));
		if (report == TYPE_LOBBY_STATUS_UPDATE){
			std::cout << "server has a lobby to send!" << std::endl;
			socket.socket_receive((char*)(&ls), sizeof(LobbyStatusData));
			std::cout << "lobby status: players:" << (int)ls.players<< "remaining time: " << (int)ls.remainingTime << std::endl;					
			gameStarted = ls.gameStarted;
				
		}
		if (report == TYPE_SERVER_SEND_MAP){
			size_t mapSize;
			socket.socket_receive((char*)(&mapSize), sizeof(mapSize));
			char mapa[mapSize];
			socket.socket_receive(mapa, mapSize);	
			std::cout << "mapa:" << std::string(mapa) << std::endl;		
		}
		if (report == TYPE_SERVER_SEND_GAME_UPDATE){
			PlayerStatus ps;
			socket.socket_receive((char*)(&ps), sizeof(PlayerStatus));
			// std::cout << "this player status - ID:" << std::to_string(ps.clientId) << std::endl;
			
			size_t size;
			socket.socket_receive((char*)(&size), sizeof(size));
			
			PlayerListItem player;
			for (int i = 0; i < size/sizeof(PlayerListItem); i++ ){
				//std::cout << "receiving player in list" << std::endl;
				socket.socket_receive((char*)(&player),sizeof(PlayerListItem));
				//std::cout << "player id:" << std::to_string(player.clientId) << std::endl;	
			}						

			socket.socket_receive((char*)(&size), sizeof(size));
			DoorListItem door;
			for (int i = 0; i < size/sizeof(DoorListItem); i++ ){
				//std::cout << "receiving door in list" << std::endl;
				socket.socket_receive((char*)(&door),sizeof(DoorListItem));
				//std::cout << "door is open:" << std::to_string(door.isOpen ? 1 : 0) << std::endl;	
			}							

			socket.socket_receive((char*)(&size), sizeof(size));
			ItemListElement item;
			for (int i = 0; i < size/sizeof(ItemListElement); i++ ){
				//std::cout << "receiving item in list" << std::endl;
				socket.socket_receive((char*)(&item),sizeof(ItemListElement));
				//std::cout << "item is visible:" << std::to_string(item.isVisible? 1 : 0) << std::endl;	
			}
		}
		if (report == TYPE_SERVER_SEND_GAME_STATISTICS){
				std::cout << "statistics - implement me!!!!!" << std::endl;
		}	
		
		//alterno entre hacer "use" y un ping
		//if (gameStarted){
			//m.type = m.type == TYPE_CLIENT_PING ? TYPE_USE_DOOR : TYPE_CLIENT_PING ;
			m.type = TYPE_CLIENT_PING  ;
			m.entityId = 0;
			size_t size = sizeof(ClientMessage);
			socket.socket_send((char*)(&size),sizeof(size));
			socket.socket_send((char*)(&m),sizeof(m));	
		//}
		
	}
} else {
	std::cout << "join unsuccessful" << std::endl;
}



}

int main(const int argc, const char* argv[]) {

	char buffer[BUF_SIZE];

	Socket socket;
	
	connectAndGetClientId(socket);
	    
    std::string line;
    while (socket.get_fd() != -1 && std::getline(std::cin, line)) {
		if (line == "q" || line == "quit") break;
		
		if (line[0] == 'j' ) {
			char mapOrGameId = std::stoi(line.substr(2,1));
			joinOrStartGame(socket,CLIENT_REQUEST_JOIN_GAME,mapOrGameId);
			
		}	

		if (line[0] == 'n') {
			char mapOrGameId = std::stoi(line.substr(2,1));
			joinOrStartGame(socket,CLIENT_REQUEST_CREATE_GAME,mapOrGameId);
			
		}
		
		//se escribio "e"
		if (line[0] == 'e') {
			//size_t length;
			//buffer[0] = TYPE_EXIT_GAME;
			//buffer[1] = 0;
			//length = 2;
			
			ClientMessage m;

			m.type = CLIENT_REQUEST_LEAVE_GAME;
			m.entityId = 0;			
			
			//envio el evento new game, ej: n 10
			std::cout << "send exit game" << std::endl;			
			socket.socket_send((char*)(&m),sizeof(m));	
			//length = 1;
			//socket.socket_receive(buffer,length);
			//if (buffer[0] == 0)
			std::cout << "exit successful" << std::endl;	
			socket.close_socket();
			break;
		}			
		
		if (line[0] == CLIENT_REQUEST_GAMES_LIST) {
			std::cout << "send request game list" << std::endl;	
			askForGameList(socket);
			getAndPrintGameList(socket);
			
		}	
				
		if (line[0] == CLIENT_REQUEST_MAPS_LIST) {
			std::cout << "send request maps list" << std::endl;	
			askForMapList(socket);
			getAndPrintMapList(socket);
			
		}			
		
	}
    return 0;
}
