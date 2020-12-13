#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include "thread.h"

class Server;

class ThreadClient : public Thread {
    Server &server;
public:
    ThreadClient(Server &server);
    virtual void run() override;
    virtual ~ThreadClient() override;
};

#endif
