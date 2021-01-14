#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

////#include <vector>
#include "../communication/thread_client.h"
#include "thread_game.h"
#include <unordered_map>
#include "../../common_src/blocking_queue.h"

/////////class ThreadClient;

class GameManager{

private:

	//BlockingQueue<std::string> messages;
	std::unordered_map<int, ThreadClient*> clientsThreads;
	std::unordered_map<int, ThreadGame*> games;
	std::unordered_map<int, int> clientsInGames;
	int games_counter;
	

	ThreadGame game; //aqui deberia haber un conjunto de Games, por ahora manejo uno.
	//ThreadClient* c;

public:

	int clients_counter;
	
	void pushMessage(std::string m);

	GameManager();
	~GameManager();
	void acceptClient(std::string socket,BlockingQueue<std::string>& q);
	
};

#endif
