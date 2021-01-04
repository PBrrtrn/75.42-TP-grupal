#ifndef CLIENT
#define CLIENT
#include <iostream>
#include <string>
#include "../common_src/blocking_queue.h"
#include "server.h"

class Server;

class Client{
	BlockingQueue<std::string> send_queue;
	Server server;
	int id;
	
public:
	Client();
	~Client();
	void startGame();
};

#endif
