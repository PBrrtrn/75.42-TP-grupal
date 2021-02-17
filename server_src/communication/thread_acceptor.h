#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include "../../common_src/Socket.h"
#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include <unordered_map>
#include "../../common_src/Thread.h"
#include "../games/game_manager.h"
#include "../../common_src/blocking_queue.h"
#include "message_processor.h"
#include "message.h"
#include "../server_config.h"

class GameManager;

class ThreadAcceptor: public Thread {

    private:
        Socket socket;
        BlockingQueue<Message> messages;
        GameManager gameManager;

        /** 
         * @brief Numero siempre creciente
         * para asignar un ID numerico
         * a cada cliente nuevo
         */
        int clients_counter;

        std::atomic<bool> keep_running{true};

    public:

        ThreadAcceptor();
        void acceptConnection();
        virtual void run() override;
        void shutdown();
        virtual ~ThreadAcceptor() override;
};

#endif
