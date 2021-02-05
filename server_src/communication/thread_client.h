#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <atomic>
#include "../../common_src/Thread.h"
#include "../../common_src/Socket.h"
#include "../../common_src/blocking_queue.h"
#include "../games/game_status.h"
#include "message.h"
#include "../../common_src/GameListItem.h"
#include "../games/lobbyStatus.h"
#include "../games/ServerStatus.h"
#include "../maps/mapListItem.h"

#include <unistd.h>  //removeme

#define BUF_SIZE 64


class ThreadClient : public Thread {
private:
	int id;
    BlockingQueue<Message>& messages;
    BlockingQueue<Message>* messages_out;
    Socket peer;
    std::atomic<bool> keep_running{true};
    std::atomic<bool> dead{false};
    ServerStatus serverStatus;
    LobbyStatus& lobbyStatus;
    bool choosing_game;
    
	void sendJoinOk();
	void sendJoinRefused();

public:

    ThreadClient(int id, BlockingQueue<Message>& messages, 
        BlockingQueue<Message>* messagesOut, Socket&& socket, 
        ServerStatus& serverStatus, LobbyStatus& lobbyStatus);
    virtual void run() override;    
    void shutdown();

    /**
     * @brief Guarda un puntero a la cola bloqueante
     * de mensajes para recibir respuesta del game manager
     * @param messages_out: cola bloqueante compartida con el
     * game manager
     */
    void assignToOutQueue(BlockingQueue<Message>* messages_out);

    /**
     * @brief Envia al cliente la lista de juegos disponibles
     * activos en el momento en el que pidió el refresh
     */
    void sendGamesList();

    /**
     * @brief Envia al cliente la lista de mapas disponibles
     */
    void sendMapsList();

    /**
     * @brief Envia al cliente el estado del lobby
     * de la partida correspondiente
     * @param gameID: id del game que mando el mensaje
     */
    void sendLobbyStatus(int gameID);

    /**
     * @brief Envia al cliente su numero
     * de jugador asignado a través del socket.
     */
    void informClientId();

    virtual ~ThreadClient() override;
};

#endif
