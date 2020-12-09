#ifndef SERVER
#define SERVER
#include <iostream>
#include <string>
#include <vector>
#include "GameStatus.h"
#include "ThreadClient.h"
#include "Client.h"
#include "Actions/Action.h"

class Server{
	std::vector<Client*> clients;
	GameStatus gameStatus;
	Map map;
	int clientCounter;
	std::vector<ThreadClient*> clientsThreads;
	void tryMovement(int id, int direction);
	void tryRotation(int id, int direction);

public:
	Server();
	void addClient(Client *client);
	void newAction(Action* action);
	void newClient();
    void tryMoveForward(int id);
    void tryMoveBackward(int id);
    void tryRotationLeft(int id);
    void tryRotationRight(int id);
	~Server();
};

#endif
