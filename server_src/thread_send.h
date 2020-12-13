#ifndef THREAD_SEND_H
#define THREAD_SEND_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include "thread.h"


class Server;

class ThreadSend: public Thread {
    BlockingQueue<Action>& messages;
    Server& server;

    public:
    ThreadSend(BlockingQueue<Action>& messages, Server& server);
    virtual void run() override;
    virtual ~ThreadSend() override;
};

#endif
