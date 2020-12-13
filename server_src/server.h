#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>

#include "thread_client.h"
#include "action.h"
#include "Client.h"
#include "game_status.h"

class Server{
	std::vector<Client*> clients;
	GameStatus gameStatus;
	Map map;
	int clientCounter;
	std::vector<ThreadClient*> clientsThreads;

public:
	Server();
	void addClient(Client *client);
	void newAction(Action action);
	void newClient();
    void tryMoveForward(int id);
    void tryMoveBackward(int id);
    void tryMoveLeft(int id);
    void tryMoveRight(int id);
    void tryShoot(int id);
	~Server();
};

#endif
