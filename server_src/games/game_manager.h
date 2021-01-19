#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "../communication/thread_client.h"
#include "thread_game.h"
#include <unordered_map>
#include "../../common_src/blocking_queue.h"
#include "../communication/message.h"

class GameManager{

private:

	/* clave: clientId value: thClient*/
	std::unordered_map<int, ThreadClient*> clientsThreads;

	/* clave: gameId value: thGame*/
	std::unordered_map<int, ThreadGame*> games;

	/* clave: gameId value: gameQueue*/
	std::unordered_map<int, BlockingQueue<Message>*> queues;

	/* clave: clientId value: gameQueue*/
	std::unordered_map<int, BlockingQueue<GameStatus>*> out_queues;
	
	/* clave: gameId value: gameQueue*/
	std::unordered_map<int, BlockingQueue<GameStatus>*> out_game_queues;	

	/* clave:clientId, value:gameId*/
	std::unordered_map<int, int> clientsInGames;
	int games_counter;
	
	/**
	 * @brief Funcion para crear una nueva partida
	 * Crea una nueva cola bloqueante para la nueva partida
	 * Crea un nuevo ThreadGame
	 * Agrega el cliente a la partida
	 * Da inicio a la partida
	 * @param clientIdStarter : id del jugador que inicia la partida
	 * y es agregado a ella (primer jugador)
	 */
	void startGame(int clientIdStarter);

	/**
	 * @brief Funcion para unir a un jugador a una 
	 * partida pre-existente
	 * @param clientId : id del cliente a agregar
	 * @param gameId : id del juego al que debe ser agregado
	 */
	void joinGame(int clientId, int gameId);

	/**
	 * @brief Funcion encargada de parsear el
	 * mensaje recibido del cliente
	 * @param Message: mensaje compuesto recibido 
	 */
	void _parse_message(Message m);

public:

	GameManager();

	int clients_counter;

	/**
	 * @brief Recibe un mensaje y se ocupa de parsearlo
	 * para efectuar la accion correspondiente
	 */
	void newMessage(Message m);
	
	void cleanUpDeadGames();
	
	/**
	 * @brief Crea un nuevo ThreadClient con el id
	 * correspondiente al contador de clientes
	 * Le pasa al thread cliente la cola para 
	 * recibir mensajes (queue in)
	 * @param q: cola bloqueante para enviar al servidor
	 * los mensajes enviados por el cliente
	 */
	void acceptClient(std::string socket,BlockingQueue<Message>& q);

	void updateClients();

	~GameManager();
};

#endif
