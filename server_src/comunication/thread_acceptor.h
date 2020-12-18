#ifndef THREAD_SEND_H
#define THREAD_SEND_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include "thread.h"
#include "thread_client.h"
#include "game_status.h"

class ThreadAcceptor: public Thread {
    //Socket socket;
    GameStatus gs;
    std::list<ThreadClient*> clients;
    std::atomic<bool> keep_running{true};

	std::vector<ThreadClient*> clientsThreads;

    public:
    ThreadAcceptor(/*const Socket& socket, */);
    virtual void run() override;
    void newClient();
    //void stop();
    //void garbage_collector();
    virtual ~ThreadAcceptor() override;
};

#endif
