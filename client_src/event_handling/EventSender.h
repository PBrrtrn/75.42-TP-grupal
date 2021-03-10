#ifndef __EVENT_SENDER_H__
#define __EVENT_SENDER_H__

#include <atomic>

#include "../../common_src/Thread.h"

#include "../ServerConnection.h"
#include "../../common_src/blocking_queue.h"
#include "../../common_src/ClientMessage.h"

class EventSender : public Thread {
private:
	BlockingQueue<ClientMessage>& message_queue;
	ServerConnection& server_connection;
	std::atomic<bool> running;
public:
	EventSender(BlockingQueue<ClientMessage>& message_queue,
							ServerConnection& server_connection);
	~EventSender();
	void run();
	void stop();
};

#endif