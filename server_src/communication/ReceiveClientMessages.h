#ifndef RECEIVE_CLIENT_MESSAGES_H
#define RECEIVE_CLIENT_MESSAGES_H

#include <atomic>
#include "../../common_src/Thread.h"
#include "../../common_src/Socket.h"
#include "../../common_src/protected_queue.h"
#include "../../common_src/ClientMessage.h"
#include "message.h"

#include <unistd.h>  //removeme

#define BUF_SIZE 64


class ReceiveClientMessages : public Thread {
private:
	int id;
    ProtectedQueue<Message>* messages;
    Socket peer;
    std::atomic<bool> keep_running{true};
    std::atomic<bool> dead{false};
	
public:

    /**
     * @brief Hilo que recibe los mensajes
     * enviados por el cliente, para ser
     * procesados en el servidor
     */
    ReceiveClientMessages(Socket&& socket, ProtectedQueue<Message>* messages);
    virtual void run() override;    
    void shutdown();

    /**
     * @brief Para realizar pasaje y empezar
     * a encolar los mensajes en la cola
     * protegida del correspondiente th game
     */
    void assignToGameQueue(ProtectedQueue<Message>* messages);

    virtual ~ReceiveClientMessages() override;
};

#endif
