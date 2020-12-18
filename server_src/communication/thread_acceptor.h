#ifndef THREAD_SEND_H
#define THREAD_SEND_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include "thread.h"
#include "../comunication/thread_client.h"
#include "../comunication/message_parser.h"
#include "../games/thread_game.h"

class ThreadAcceptor: public Thread {
    //Socket socket;
    std::list<ThreadGame*> games;
    //std::list<ThreadClient*> clients;
    MessageParser message_parser;
    std::atomic<bool> keep_running{true};

	std::vector<ThreadClient*> clientsThreads;

    public:
    ThreadAcceptor(/*const Socket& socket, */);
    virtual void run() override;
    void newClient();
    void newMessage(std::string message);
    //void stop();
    //void garbage_collector();
    virtual ~ThreadAcceptor() override;
};

#endif
