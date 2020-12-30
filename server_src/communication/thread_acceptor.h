#ifndef THREAD_SEND_H
#define THREAD_SEND_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include <unordered_map>
#include "thread.h"
#include "thread_client.h"
#include "../games/thread_game.h"

class ThreadAcceptor: public Thread {
    //Socket socket;
    int clients_counter;
    std::unordered_map<int, ThreadClient*> clientsThreads;
    std::unordered_map<int, ThreadGame&> clientsGames;

    int games_counter;
    std::unordered_map<int, ThreadGame*> games;

    std::atomic<bool> keep_running{true};

    void _parse_message(std::string message, int clientID);

    public:

    ThreadAcceptor(/*const Socket& socket, */);

    virtual void run() override;
    /**
     * @brief Inicia un nuevo hilo cliente y guarda el mismo en
     * el mapa de hilos cliente, usando como clave
     * el numero que indica el contador de clientes
     * al momento de ser agregado.
     *
    */
    void newClient();

    void newMessage(std::string message, int clientID);

    //void stop();
    //void garbage_collector();

    virtual ~ThreadAcceptor() override;
};

#endif
