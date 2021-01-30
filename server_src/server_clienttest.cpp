#include <iostream>

#include "../common_src/Socket.h"

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
	
	//envio evento start si soy el primer client, buffer[0] = evento, buffer[1] = mapId
	if (clientId == "0"){
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
