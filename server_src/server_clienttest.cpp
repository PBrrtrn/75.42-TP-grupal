#include <iostream>

#include "../common_src/Socket.h"

int main(const int argc, const char* argv[]) {

	Socket socket;

	bool resultado = socket.socket_connect("localhost","666");
	
	char buffer[20];
	int length;
	
	socket.socket_receive(buffer,length);
	
	buffer[length] = '\0';
	
	std::string clientId = std::to_string(buffer[0]);
	
	std::cout << clientId << std::endl;

    return 0;
}
