#include <iostream>
#include <string>
#include "Client.h"
#include "Server.h"
#include <stdio.h>
#include <thread>

//Al tener sockets el cliente conoce al servidor por
//la conexion establecida.



int main(){

	Server server;
	//Client client(server);
    //Client client2(server);
    server.newClient();
    //server.newClient(); TODO no se puede probar

	std::cout << "GAME SETUP" << std::endl;

    return 0;
}
