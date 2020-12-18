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

public:
    ThreadClient(ThreadAcceptor& acceptor);
    virtual void run() override;
    void stop();
    bool is_dead();
    virtual ~ThreadClient() override;
};

#endif
