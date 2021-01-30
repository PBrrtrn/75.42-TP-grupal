#ifndef THREAD_CLIENT_H
#define THREAD_CLIENT_H

#include <atomic>
#include "../../common_src/Thread.h"
#include "../../common_src/Socket.h"
#include "../../common_src/blocking_queue.h"
#include "../games/game_status.h"
#include "message.h"
#include "../../common_src/GameListItem.h"
#include "../games/ServerStatus.h"

#include <unistd.h>  //removeme

#define BUF_SIZE 64


class ThreadClient : public Thread {

	int id;
    BlockingQueue<Message>& messages;
    BlockingQueue<Message>* messages_out;
    Socket peer;
    std::atomic<bool> keep_running{true};
    std::atomic<bool> dead{false};
    ServerStatus serverStatus;
    bool choosing_game;

public:

    ThreadClient(int id, BlockingQueue<Message>& messages, 
        BlockingQueue<Message>* messagesOut, Socket&& socket, 
        ServerStatus& serverStatus);
    virtual void run() override;    
    void shutdown();
    void assignToOutQueue(BlockingQueue<Message>* messages_out);
    virtual ~ThreadClient() override;
};

#endif
