#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

//#include <mutex>
#include <atomic>
#include "thread.h"
#include "../common_src/socket.h"
#include "thread_acceptor.h"

#define BUF_SIZE 64

class Server;

class ThreadClient : public Thread {
    Socket* peer;
    //Server &server;
    //std::mutex mtx;
    std::atomic<bool> keep_running{true};
    std::atomic<bool> dead{false};

    ThreadAcceptor& acceptor;
    int id;

public:
    ThreadClient(ThreadAcceptor& acceptor, int id);
    
    /**
     * @brief Entrega al hilo aceptador
     * el mensaje enviado por el cliente.
     */
    virtual void run() override;
    //void stop();
    //bool is_dead();
    virtual ~ThreadClient() override;
};

#endif
