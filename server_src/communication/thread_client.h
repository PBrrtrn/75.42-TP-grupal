#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

//#include <mutex>
#include <atomic>
#include "../../common_src/thread.h"
#include "../../common_src/socket.h"
#include "../../common_src/blocking_queue.h"
////#include "../games/game_manager.h"
////#include "thread_acceptor.h"

#define BUF_SIZE 64

////class ThreadAcceptor;
////class GameManager;

class ThreadClient : public Thread {
    Socket* peer;
    //Server &server;
    //std::mutex mtx;
    std::atomic<bool> keep_running{true};
    std::atomic<bool> dead{false};

    BlockingQueue<std::string>& messages;
    int id;

public:

    ThreadClient(int id, BlockingQueue<std::string>& messages);
    //ThreadClient(int id, BlockingQueue<std::string>& messages);
    
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