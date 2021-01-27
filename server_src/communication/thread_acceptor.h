#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include "../../common_src/Socket.h"
#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include <unordered_map>
#include "../../common_src/Thread.h"
#include "../games/game_manager.h"
#include "../../common_src/blocking_queue.h"
#include "message_processor.h"
#include "message.h"


class GameManager;

class ThreadAcceptor: public Thread {

    MessageProcessor message_processor;
    Socket socket;
    
    BlockingQueue<Message> messages;
    

	GameManager gameManager;

    /** 
     * @brief Numero siempre creciente
     * para asignar un ID numerico
     * a cada cliente nuevo
     */
    int clients_counter;

    std::atomic<bool> keep_running{true};

    public:

    ThreadAcceptor();
    
    void acceptConnection();

    virtual void run() override;

    /**
     * @brief Inicia un nuevo hilo cliente y guarda el mismo en
     * el mapa de hilos cliente, usando como clave
     * el numero que indica el contador de clientes
     * al momento de ser agregado.
     *
    */
    void newClient();

    /**
     * @brief Parsea el mensaje recibido y efectúa 
     * la acción correspondiente.
     */
    void newMessage(std::string message, int clientID);

    //void garbage_collector();

    virtual ~ThreadAcceptor() override;
};

#endif
