#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

////#include <vector>
#include "../communication/thread_client.h"
#include "thread_game.h"
#include <unordered_map>

class GameManager : public Thread {

private:

	BlockingQueue<std::string> messages;
	std::unordered_map<int, ThreadClient*> clientsThreads;
	std::unordered_map<int, ThreadGame*> games;
	std::unordered_map<int, int> clientsInGames;
	int games_counter;
	int clients_counter;

	void _parse_message(std::string message, int clientID);

	ThreadGame game; //aqui deberia haber un conjunto de Games, por ahora manejo uno.
	//ThreadClient* c;

public:

	GameManager();

	void acceptClient(std::string socket, BlockingQueue<std::string>& messages_internos);

	/**
     * @brief Parsea el mensaje recibido y efectúa 
     * la acción correspondiente.
     */
    void newMessage(std::string message, int clientID);
	virtual void run() override;

	virtual ~GameManager() override;
	
};

#endif
