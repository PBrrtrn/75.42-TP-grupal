#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>

#include "./communication/thread_acceptor.h"

//#include <fstream>

class Server {
	//const char* server_port;
	//Socket socket;
	ThreadAcceptor acceptor;
	//BlockingQueue<std::string>& messages;

	public:
		
		//Server(BlockingQueue<std::string>& messages);
		Server();
		/**
		 * @brief Crea un hilo aceptador
		 * para recibir conexiones de
		 * multiples clientes
		 */
		void start();

		/**
		 * @brief Devuelve true en caso de un bind and
		 * listen exitoso del socket, 
		 * false en caso contrario
		*/
		//bool ready_to_receive();

		/**
		 * @brief Cierra el hilo aceptador 
		 * y lo elimina
		 */
		~Server();
		
};

#endif
