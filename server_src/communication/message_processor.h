#ifndef __MESSAGE_PROCESSOR_H__
#define __MESSAGE_PROCESSOR_H__

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include <unordered_map>
#include "../../common_src/Thread.h"
#include "../../common_src/blocking_queue.h"
#include "../games/game_manager.h"
#include "message.h"

class MessageProcessor: public Thread {
	private:
        GameManager& gameManager;
        std::atomic<bool> keep_running;

    public:
        MessageProcessor(GameManager& gm);

        virtual void run() override;

        void shutdown();
        
        virtual ~MessageProcessor() override;
};

#endif
