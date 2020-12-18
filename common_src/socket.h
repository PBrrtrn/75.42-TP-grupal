#ifndef SOCKET_H
#define SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netdb.h>
#include <errno.h>

#include <iostream>

#define FAMILY AF_INET
#define PROTOCOL 0
#define SOCK_TYPE SOCK_STREAM
#define SERVER_FLAGS AI_PASSIVE
#define CLIENT_FLAGS 0

class Socket {
    private:
        int fd;
        //Devuelve una lista de posibles direcciones para conectarse.
        struct addrinfo* _get_addrinfo(const char* host, 
            const char* service, int flags);

    public:
        //Inicializa un socket.
        Socket();

        //Devuelve true si pudo conectarse a un puerto y 
        //activarse para recibir conexiones,
        //false en caso de error.
        bool socket_bind_and_listen(const char* host, const char* service);

        //Devuelve el fd asociado al socket
        int& get_fd();

        //Acepta una conexion y devuelve
        // el fd en caso exitoso, 
        //-1 en caso de error.
        int socket_accept(Socket* listener);

        //Devuelve true si la conexión fue exitosa, false en caso de error.
        bool socket_connect(const char* host, const char* service);

        //Devuelve la cantidad de bytes enviados o -1 si ocurrió un error.
        ssize_t socket_send(const char* buffer, size_t length);

        //Devuelve la cantidad de bytes recibidos o -1 si ocurrió un error.
        ssize_t socket_receive(char* buffer, size_t length);

        //Cierra y hace un shutdown del socket.
        ~Socket();
};

#endif
