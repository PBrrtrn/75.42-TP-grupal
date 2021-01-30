#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>

#include "./communication/thread_acceptor.h"
#include "server_config.h"

class Server {
	private:
	ThreadAcceptor acceptor;

	public:
	Server();
	/**
	 * @brief Crea un hilo aceptador
	 * para recibir conexiones de
	 * multiples clientes
	 */
	void start();

	/**
	 * @brief Cierra el hilo aceptador 
	 * y lo elimina
	 */
	~Server();
};

#endif
