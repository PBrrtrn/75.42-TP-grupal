#include "Socket.h"

/*Si is_server == true, se usara como aceptador 
 * (acceptOn y getReceiveSocket), de otra forma sera cliente
 * (connectTo)*/
Socket::Socket(bool is_server){
	this->fd = -1;
	this->server = is_server;
	memset(&(this->datos_conexion), 0, sizeof(struct addrinfo));
	this->datos_conexion.ai_family = AF_INET;       
	this->datos_conexion.ai_socktype = SOCK_STREAM;
	this->datos_conexion.ai_flags = this->server? AI_PASSIVE : 0; 	
	this->lista_direcciones = NULL;
}

Socket::Socket(Socket&& from){
	this->server = from.server;
	this->lista_direcciones = from.lista_direcciones;
	this->fd = from.fd;
	from.fd = -1;
}

/* Abre un canal a remote_address en el puerto protocol.
 * Si es server, se ignora el valor de remote_address. */
int Socket::connectTo(std::string remote_address,std::string protocol){
	int result = -1;
	result = getaddrinfo(this->server ? NULL : remote_address.c_str(),
						protocol.c_str(), 
						&(this->datos_conexion), 
						&(this->lista_direcciones));
	
	/*Si getaddrinfo tuvo un error, termino y lo devuelvo.*/
	if (result){
		return result;
	} else {
		struct addrinfo* current;
		for (current = this->lista_direcciones; current != NULL; 
										current = current->ai_next) {
			this->fd = socket(current->ai_family, 
							 current->ai_socktype, 
							 current->ai_protocol);
			result = connect(this->fd,
					current->ai_addr, 
					current->ai_addrlen);	
			
			if (result == 0)
				break;
		}
		freeaddrinfo(this->lista_direcciones);
		
		/* Si no pudo encontrar ninguna direccion para conectarse,
		 * cierro el socket y marco el fd como invalido*/
		if (result != 0) {
			close(this->fd);
			this->fd = -1;
		}	
	}
	return 0;	
}

/* Acepta conexiones en remote_address de sockets cliente entrantes.
 * Escucha por default en localhost
 * */
int Socket::acceptOn(std::string remote_address,std::string protocol){
	int result = -1;
	result = getaddrinfo(this->server ? NULL : remote_address.c_str(),
						protocol.c_str(), 
						&(this->datos_conexion), 
						&(this->lista_direcciones));
	
	/*Si getaddrinfo tuvo un error, termino y lo devuelvo.*/
	if (result){
		return result;
	} else {
		this->fd = socket(this->lista_direcciones->ai_family, 
						 this->lista_direcciones->ai_socktype, 
						 this->lista_direcciones->ai_protocol);
		bind(this->fd, 
					this->lista_direcciones->ai_addr, 
					this->lista_direcciones->ai_addrlen);
		listen(this->fd, MAX_CLIENTS);

		freeaddrinfo(this->lista_direcciones);
	}
	return 0;	
}

/* Envia un message binario de tamanio size.
 * Reintenta hasta que logre mandarlo completo.*/
int Socket::sendByteMessage(int size,const char* message){
	if (this->fd > 0) {
		int sent = send(this->fd, message, size, MSG_NOSIGNAL);
		while (sent < size){
			char* aux_send = (char*)message + sent;
			int size_left = size - sent;
			int res = send(this->fd, aux_send, size_left, MSG_NOSIGNAL);
			if (res > 0) {
				sent += res;
			} else {
				return -1;
			}
		}
	} else {
		return -1;
	}	
	return 0;
}

/* Envia un mensaje de formato texto contenido en message.
* Reintenta hasta que logre mandarlo completo.*/
int Socket::sendMessage(const std::string& message){
	const char* m = message.c_str();
	int size = message.length();
	
	return this->sendByteMessage(size,m);
}

/* Obtiene un socket receptor asociado al aceptador, para atender
 * la conexion entrante. */
Socket Socket::getReceiveSocket(){
	Socket receiver(this->server);	
	receiver.datos_conexion.ai_family = AF_INET;       
	receiver.datos_conexion.ai_socktype = SOCK_STREAM;
	receiver.datos_conexion.ai_flags = this->server? AI_PASSIVE : 0; 		
	receiver.fd = accept(this->fd, NULL, NULL);
	
	return receiver;
}

bool Socket::isOpen(){
	return (this->fd > -1);
}

/* Recibe datos binarios y guarda en m, sin terminacion \0
 * Entrada: size indica el ancho del buffer m
 * 	m debe ser un buffer ya reservado en memoria
 * post: Se devuelve en size la cantidad de bytes leidos.*/
bool Socket::receiveByteMessage(int& message_size,char* m){
	int size;
	size = recv(this->fd, m, message_size, 0);
	int result = 1;
	while (result > 0 && size < message_size) {
		result = recv(this->fd, (m + size),message_size - size, 0);
		if (result > 0) {
			size = size + result;
		}
	}
	message_size = size;
	return (message_size > 0)? true : false;
}

/* Guarda en message un mensaje recibido. 
 * Asume que lo recibido es texto. */
bool Socket::receiveMessage(std::string& message){
	char m[MAX_BUFFER];
	int size = MAX_BUFFER;
	int total_size = 0;
	message.clear();
	
	while (this->receiveByteMessage(size,m)){
		char b[MAX_BUFFER + 1];
		snprintf(b,size + 1,"%s",m);
		message = message + std::string(b);
		total_size = total_size + size;
		size = MAX_BUFFER;
	}
	return (total_size > 0)? true : false;
}

/* Cierra la conexion completamente contra el server o client. */
void Socket::closeSocket(){
	if (this->fd > 0){
		shutdown(this->fd, SHUT_RDWR);
		close(this->fd);
	}
}

/*Realiza el shutdown contra el socket receptor del otro lado,
 * pero solo de escritura (sigue abierto para recibir)*/
void Socket::stopSending(){
	if (this->fd > 0){
		shutdown(this->fd,SHUT_WR);
	}
}

/* Libera los recursos. Cierra el socket si estuviera abierto. */
Socket::~Socket(){
	this->closeSocket();
}
