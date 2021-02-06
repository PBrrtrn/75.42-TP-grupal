#include <iostream>
#include <unistd.h>

#include "../common_src/Socket.h"
#include "../common_src/GameListItem.h"
#include "./maps/mapListItem.h"
#include "./communication/message.h"
#include "../common_src/LobbyStatusData.h"
#include "./games/client_game_status.h"

#define BUF_SIZE 64

void connectAndGetClientId(Socket& socket){
	char buffer[BUF_SIZE];
	bool resultado = socket.socket_connect("localhost","9000");
	int length = 1;
	//recibo el clientId
	socket.socket_receive(buffer,length);
	//socket.socket_send(("r"),sizeof(("r"))); //prueba, a ver que hace
	std::string clientId = std::to_string(buffer[0]);
	std::cout << "client id:" << clientId << std::endl;
	
}

void getAndPrintGameList(Socket& socket){
	char buffer[BUF_SIZE];
	int length = 1;
	//recibo el size del game list	
	socket.socket_receive(buffer,length);
	buffer[length] = '\0';	
	std::string gameListSize = std::to_string(buffer[0]);
	std::cout << "size of game list:" << gameListSize << std::endl;	
	
	GameListItem list_item;
	
	std::cout << "iterations:" << buffer[0]/sizeof(GameListItem) << std::endl;
	
	for (int i = 0; i < buffer[0]/sizeof(GameListItem); i++ ){
		std::cout << "receiving game in list" << std::endl;
		socket.socket_receive((char*)(&list_item),sizeof(GameListItem));
		std::cout << "game index:" << i << ", gameId:" <<  std::to_string(list_item.gameId) << ",players:" << std::to_string(list_item.players)<< ",maxPlayers:" << std::to_string(list_item.maxPlayers)<< ",mapId:" << std::to_string(list_item.mapId) << std::endl;	
	}	
}

void getAndPrintMapList(Socket& socket){
	char buffer[BUF_SIZE];
	int length = 1;

	socket.socket_receive(buffer,length);
	buffer[length] = '\0';	
	std::string MapListSize = std::to_string(buffer[0]);
	std::cout << "size of map list:" << MapListSize << std::endl;	
	
	MapListItem list_item;
	
	std::cout << "iterations:" << buffer[0]/sizeof(MapListItem) << std::endl;
	
	for (int i = 0; i < buffer[0]/sizeof(MapListItem); i++ ){
		std::cout << "receiving maps in list" << std::endl;
		socket.socket_receive((char*)(&list_item),sizeof(MapListItem));
		std::cout << "map index:" << i << ", map id:" <<  std::to_string(list_item.mapId) 
			<< ",players:" << std::to_string(list_item.minPlayers)<< 
			",maxPlayers:" << std::to_string(list_item.maxPlayers)<< 
			", map name:" << std::string(list_item.name) << std::endl;	
	}	
}

void askForGameList(Socket& socket){
	char buffer[BUF_SIZE];
	int length = 2;
	buffer[0] = TYPE_REFRESH_GAMES_LIST;
	buffer[1] = 0;
	
	socket.socket_send(buffer,length);
}

void askForMapList(Socket& socket){
	char buffer[BUF_SIZE];
	int length = 2;
	buffer[0] = TYPE_SEND_MAPS_LIST;
	buffer[1] = 0;
	
	socket.socket_send(buffer,length);
}

int main(const int argc, const char* argv[]) {

	char buffer[BUF_SIZE];

	Socket socket;
	
	connectAndGetClientId(socket);
	getAndPrintGameList(socket);
	    
    std::string line;
    while (socket.get_fd() != -1 && std::getline(std::cin, line)) {
		if (line == "q" || line == "quit") break;
		
		if (line[0] == TYPE_JOIN_GAME) {
			int length;
			char gameId = std::stoi(line.substr(2,1));
			buffer[0] = TYPE_JOIN_GAME;
			buffer[1] = gameId;
			length = 2;
			//envio el evento join game, ej: j 3
			std::cout << "send join game" << std::endl;	
			socket.socket_send(buffer,length);
			length = 1;
			socket.socket_receive(buffer,length);
			if (buffer[0] == 0) {
				std::cout << "join successful" << std::endl;
				LobbyStatusData ls;
				ls.gameStarted = false;
				while(!ls.gameStarted && socket.socket_receive((char*)(&ls), sizeof(LobbyStatusData))) {
					std::cout << "lobby status: players:" << (int)ls.players<< "remaining time: " << 
					(int)ls.remainingTime << std::endl;
				}
				
				socket.socket_receive((char*)(&ls), sizeof(LobbyStatusData));
				
				std::cout << "last lobby status: players:" << (int)ls.players << std::endl;
				
				while (ls.gameStarted) {
					PlayerStatus ps;
					socket.socket_receive((char*)(&ps), sizeof(PlayerStatus));
					std::cout << "this player status - ID:" << std::to_string(ps.clientId) << std::endl;
					
					int size;
					socket.socket_receive((char*)(&size), sizeof(int));
					
					PlayerListItem player;
					for (int i = 0; i < size/sizeof(PlayerListItem); i++ ){
						std::cout << "receiving player in list" << std::endl;
						socket.socket_receive((char*)(&player),sizeof(PlayerListItem));
						std::cout << "player id:" << std::to_string(player.clientId) << std::endl;	
					}						

					socket.socket_receive((char*)(&size), sizeof(int));
					DoorListItem door;
					for (int i = 0; i < size/sizeof(DoorListItem); i++ ){
						std::cout << "receiving door in list" << std::endl;
						socket.socket_receive((char*)(&door),sizeof(DoorListItem));
						std::cout << "door is open:" << std::to_string(door.isOpen ? 1 : 0) << std::endl;	
					}							

					socket.socket_receive((char*)(&size), sizeof(int));
					ItemListElement item;
					for (int i = 0; i < size/sizeof(ItemListElement); i++ ){
						std::cout << "receiving item in list" << std::endl;
						socket.socket_receive((char*)(&item),sizeof(ItemListElement));
						std::cout << "item is visible:" << std::to_string(item.isVisible? 1 : 0) << std::endl;	
					}	
				}
			}
		}

		if (line[0] == TYPE_START_GAME) {
			int length;
			char mapId = std::stoi(line.substr(2,1));
			buffer[0] = TYPE_START_GAME;
			buffer[1] = mapId;
			length = 2;
			//envio el evento new game, ej: n 10
			std::cout << "send start game" << std::endl;			
			socket.socket_send(buffer,length);
			length = 1;
			socket.socket_receive(buffer,length);
			if (buffer[0] == 0) {
				std::cout << "start successful" << std::endl;
				LobbyStatusData ls;
				ls.gameStarted = false;
				while(!ls.gameStarted && socket.socket_receive((char*)(&ls), sizeof(LobbyStatusData))) {
					std::cout << "lobby status: players:" << (int)ls.players<< "remaining time: " << 
					(int)ls.remainingTime << std::endl;
				}
				
				socket.socket_receive((char*)(&ls), sizeof(LobbyStatusData));
				
				std::cout << "last lobby status: players:" << (int)ls.players << std::endl;				
				
				while (ls.gameStarted) {
					PlayerStatus ps;
					socket.socket_receive((char*)(&ps), sizeof(PlayerStatus));
					std::cout << "this player status - ID:" << std::to_string(ps.clientId) << std::endl;
					
					int size;
					socket.socket_receive((char*)(&size), sizeof(int));
					
					PlayerListItem player;
					for (int i = 0; i < size/sizeof(PlayerListItem); i++ ){
						std::cout << "receiving player in list" << std::endl;
						socket.socket_receive((char*)(&player),sizeof(PlayerListItem));
						std::cout << "player id:" << std::to_string(player.clientId) << std::endl;	
					}						

					socket.socket_receive((char*)(&size), sizeof(int));
					DoorListItem door;
					for (int i = 0; i < size/sizeof(DoorListItem); i++ ){
						std::cout << "receiving door in list" << std::endl;
						socket.socket_receive((char*)(&door),sizeof(DoorListItem));
						std::cout << "door is open:" << std::to_string(door.isOpen ? 1 : 0) << std::endl;	
					}							

					socket.socket_receive((char*)(&size), sizeof(int));
					ItemListElement item;
					for (int i = 0; i < size/sizeof(ItemListElement); i++ ){
						std::cout << "receiving item in list" << std::endl;
						socket.socket_receive((char*)(&item),sizeof(ItemListElement));
						std::cout << "item is visible:" << std::to_string(item.isVisible? 1 : 0) << std::endl;	
					}	
				}
			}
							
		}		
		
		//se escribio "e"
		if (line[0] == TYPE_EXIT_GAME) {
			int length;
			buffer[0] = TYPE_EXIT_GAME;
			buffer[1] = 0;
			length = 2;
			//envio el evento new game, ej: n 10
			std::cout << "send exit game" << std::endl;			
			socket.socket_send(buffer,length);
			length = 1;
			//socket.socket_receive(buffer,length);
			//if (buffer[0] == 0)
			std::cout << "exit successful" << std::endl;	
			socket.close_socket();
			break;
		}			
		
		if (line[0] == TYPE_REFRESH_GAMES_LIST) {
			std::cout << "send request game list" << std::endl;	
			askForGameList(socket);
			getAndPrintGameList(socket);
			
		}	
				
		if (line[0] == TYPE_SEND_MAPS_LIST) {
			std::cout << "send request maps list" << std::endl;	
			askForMapList(socket);
			getAndPrintMapList(socket);
			
		}			
		
	}
    return 0;
}
