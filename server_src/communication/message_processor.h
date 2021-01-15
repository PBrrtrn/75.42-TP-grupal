#ifndef __MESSAGE_PROCESSOR_H__
#define __MESSAGE_PROCESSOR_H__

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include <unordered_map>
#include "../../common_src/thread.h"
#include "../../common_src/blocking_queue.h"

class MessageProcessor: public Thread {

	private:

    BlockingQueue<std::string>& messages;

    std::atomic<bool> keep_running{true};

    public:

    MessageProcessor(BlockingQueue<std::string>& m);

    virtual void run() override;
    
    void checkNews();

    virtual ~MessageProcessor() override;
};

#endif
