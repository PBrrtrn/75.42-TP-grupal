//
// Created by alejo on 29/11/20.
//

#ifndef TP_FINAL_WOLFENSTEIN_3D_THREADCLIENT_H
#define TP_FINAL_WOLFENSTEIN_3D_THREADCLIENT_H

#include "Thread.h"
class Server;

class ThreadClient : public Thread {
    Server &server;
public:
    ThreadClient(Server &server);
    virtual void run() override;
    virtual ~ThreadClient() override;
};


#endif //TP_FINAL_WOLFENSTEIN_3D_THREADCLIENT_H
