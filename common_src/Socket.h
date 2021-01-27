#ifndef __SOCKET_H__
#define __SOCKET_H__

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>

#define MAX_CLIENTS 25
#define MAX_BUFFER 16

class Socket{
private:
	struct addrinfo datos_conexion;
	struct addrinfo* lista_direcciones;
	bool server;
	int fd;
	
public:
	/*Si is_server == true, se usara como aceptador 
	 * (acceptOn y getReceiveSocket), de otra forma sera cliente
	 * (connectTo)*/
	explicit Socket(bool is_server);
	Socket(Socket&& from);
	
	Socket(const Socket&) = delete;	

	/* Abre un canal a remote_address en el puerto protocol.
	 * Si es server, se ignora el valor de remote_address.
	 * */
	int connectTo(std::string remote_address,std::string protocol);

	/* Acepta conexiones en remote_address de sockets cliente entrantes.
	 * Escucha por default en localhost
	 * */
	int acceptOn(std::string remote_address,std::string protocol);

	/* Envia un mensaje de formato texto contenido en message.
	* Reintenta hasta que logre mandarlo completo.*/
	int sendMessage(const std::string& message);
	
	/* Envia un message binario de tamanio size.
	 * Reintenta hasta que logre mandarlo completo.*/
	int sendByteMessage(int size,const char* message);

	/* Obtiene un socket receptor asociado al aceptador, para atender
	 * la conexion entrante. */
	Socket getReceiveSocket();
	
	bool isOpen();

	/* Guarda en message un mensaje recibido. 
	 * Asume que lo recibido es texto. */
	bool receiveMessage(std::string& message);
	
	/* Recibe datos binarios y guarda en m, sin terminacion \0
	 * Entrada: size indica el ancho del buffer m
	 * 	m debe ser un buffer ya reservado en memoria
	 * post: Se devuelve en size la cantidad de bytes leidos.*/
	bool receiveByteMessage(int& size,char* message);

	/* Cierra la conexion completamente contra el server o client. */
	void closeSocket();
	

	/*Realiza el shutdown contra el socket receptor del otro lado,
	* pero solo de escritura (sigue abierto para recibir)*/
	void stopSending();	

	/* Libera los recursos. Cierra el socket si estuviera abierto. */
	~Socket();
};

#endif
