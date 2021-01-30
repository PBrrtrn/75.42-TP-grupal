#include <iostream>

#include "../common_src/Socket.h"
#include "../common_src/GameListItem.h"

#define BUF_SIZE 64

int main(const int argc, const char* argv[]) {

	Socket socket;

	bool resultado = socket.socket_connect("localhost","9001");
	
	char buffer[BUF_SIZE];
	int length = 1;

	//recibo el clientId
	socket.socket_receive(buffer,length);
	std::string clientId = std::to_string(buffer[0]);
	std::cout << "client id:" << clientId << std::endl;

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
		std::cout << "socket pos:" << i << ", data:" <<  std::to_string(list_item.gameId) << " " << std::to_string(list_item.players)<< " " << std::to_string(list_item.maxPlayers)<< " " << std::to_string(list_item.mapId) << std::endl;	
	}
	
	
	
	//char buffer_list[gameListSize];
	
	//envio evento start si soy el primer client, buffer[0] = evento, buffer[1] = mapId
	if (clientId == "0" || clientId == "1"){
		buffer[0] = 'n';
		buffer[1] = 2;
	} else {
		buffer[0] = 'j';
		buffer[1] = 0;		
	}
	length = 2;
	
	socket.socket_send(buffer,length);


    return 0;
}
