#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "../../common_src/Socket.h"
#include "../communication/thread_client.h"
#include "thread_game.h"
#include <unordered_map>
#include "../../common_src/blocking_queue.h"
#include "../../common_src/protected_queue.h"
#include "../communication/message.h"
#include "ServerStatus.h"
#include "../../common_src/GameListItem.h"
#include "./lobbyStatus.h"
#include "../maps/mapRepository.h"
#include "../communication/ReceiveClientMessages.h"

class GameManager{

private:

	BlockingQueue<Message> lobby_messages;

	/* clave: gameId value: GameListItem*/
	std::unordered_map<int, GameListItem> games_list;

	ServerStatus serverStatus;
	LobbyStatus lobbyStatus;
	MapRepository mapsRepo;

	/* clave: clientId value: thClient*/
	std::unordered_map<int, ThreadClient*> clientsThreads;

	/* clave: clientId value: ReceiveClientMessages*/
	std::unordered_map<int, ReceiveClientMessages*> clientMessageReceiver;

	/* clave: gameId value: thGame*/
	std::unordered_map<int, ThreadGame*> games;

	/* clave: gameId value: gameQueue*/
	std::unordered_map<int, ProtectedQueue<Message>*> messageReceiver;

	/* clave: clientId value: gameQueue*/
	std::unordered_map<int, BlockingQueue<Message>*> out_queues;

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
	 * @param mapId: id del mapa con el que quiere crear la partida
	 */
	void startGame(int clientIdStarter, int mapId);

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
	
	void expelClient(int expelledClientId);

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
	 */
	void acceptClient(Socket&& socket);
	
	/**
	 * @brief Envia al cliente la lista de las partidas
	 * que estan disponibles para unirse
	 * @param clientId: id del cliente al cual le envia
	 * la informacion
	 */
	void informAvailableGames(int clientId);

	/**
	 * @brief Envia al cliente la lista de mapas
	 * disponibles para crear partidas
	 * @param clientId: id del cliente al que 
	 * hay que mandarle la lista
	 */
	void sendMapsList(int clientId);

	void receiveMessages();

	void closeBlockingQueue();

	~GameManager();
};

#endif
