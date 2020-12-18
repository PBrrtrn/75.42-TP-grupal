#define _POSIX_C_SOURCE 200112L
#include "socket.h"

Socket:: Socket(){
    this->fd = -1;
}

struct addrinfo* Socket:: _get_addrinfo
(const char* host, const char* service, int flags) {
	int error;
	struct addrinfo *addr_list;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = FAMILY;
    hints.ai_socktype = SOCK_TYPE;
    hints.ai_protocol = PROTOCOL;    
	hints.ai_flags = flags;
	if ((error = getaddrinfo(host, service, &hints, &addr_list)) != 0) {
		fprintf(stderr, "_get_addrinfo: %s\n", gai_strerror(error));
        return NULL;
    }
	return addr_list;
}

bool Socket::socket_bind_and_listen(const char* host, const char* service){
	bool bind_error = false;
	int fd;
	int val = 1;
	struct addrinfo *addr, *addr_list;
	if ((addr_list = _get_addrinfo(host, service, SERVER_FLAGS)) == NULL) {
        return false;
    }

	for (addr = addr_list; addr && !bind_error; addr = addr->ai_next) {
        fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (bind(fd, addr->ai_addr, addr->ai_addrlen) == 0) bind_error = true;
    }
    freeaddrinfo(addr_list);
    
    if (!bind_error) {
		fprintf(stderr, "socket_bind_and_listen-->bind: %s\n", strerror(errno));
        return false;
    }

	this->fd = fd;

	if (listen(this->fd, 10) < 0) {
		fprintf(stderr, "socket_bind_and_listen-->listen: %s\n", strerror(errno));
		return false;
	}

	return true;
}

int& Socket:: get_fd(){
    return this->fd;
}

int Socket:: socket_accept(Socket* listener){    
	if ((this->fd = accept(listener->get_fd(), NULL, NULL)) < 0) {
		//fprintf(stderr, "socket_accept-->accept: %s\n", strerror(errno));
	}
	return this->fd;
}

bool Socket:: socket_connect(const char* host, const char* service){
	int fd;
	bool connection = false;

    struct addrinfo *addr, *addr_list;
    if ((addr_list = _get_addrinfo(host, 
        service, CLIENT_FLAGS)) == NULL) {
        return false;
    }

    for (addr = addr_list; addr && !connection; addr = addr->ai_next) {
        fd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (connect(fd, addr->ai_addr, addr->ai_addrlen) != -1) {
            connection = true;
        }
    }
    freeaddrinfo(addr_list);

    if (!connection) {
		fprintf(stderr, "socket_connect-->connect: %s\n", strerror(errno));
        return false;
    }

	this->fd = fd;
    return true;
}

ssize_t Socket:: socket_send(const char* buffer, size_t length){
	if (length == 0) return 0;

    int remaining_bytes = length;
    size_t total_bytes_sent = 0;

    while (total_bytes_sent < length) {
        ssize_t bytes = send(this->fd, &buffer[total_bytes_sent], 
                        remaining_bytes, MSG_NOSIGNAL);

        if (bytes == -1) {
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }

    return total_bytes_sent;
}

ssize_t Socket:: socket_receive(char* buffer, size_t length){
	if (length == 0) return 0;

    int remaining_bytes = length;
    size_t total_bytes_received = 0;

    while (total_bytes_received < length) {
        ssize_t bytes = recv(this->fd, &buffer[total_bytes_received],
                        remaining_bytes, 0);

        if (bytes == -1) {
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    return total_bytes_received;
}

Socket:: ~Socket(){
    if (this->fd != -1) {
        if (close(this->fd) == -1) {
		    //fprintf(stderr, "socket_uninit-->close: %s\n", strerror(errno));
        }
    }
}
