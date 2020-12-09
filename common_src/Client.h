#ifndef CLIENT
#define CLIENT
#include <iostream>
#include <string>
#include "Map.h"
#include "GameStatus.h"
#include "Drawing/Drawer.h"
#include "BlockingQueue.h"
#include "ThreadSend.h"
#include "Drawing/thread_draw.h"
#include "Actions/Action.h"

class Server;

class Client{
	Drawer drawer;
	BlockingQueue<Action*> send_queue;
	ThreadSend thSend;
	int id;
	
public:
	Client(Server &server);
	~Client();
	void startGame(GameStatus& gStatus, int clientID);
};

#endif
