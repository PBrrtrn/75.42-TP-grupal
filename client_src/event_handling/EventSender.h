#ifndef __EVENT_SENDER_H__
#define __EVENT_SENDER_H__

#include <atomic>

#include "../../common_src/Thread.h"

#include "Request.h"
#include "../ServerConnection.h"
#include "../../common_src/blocking_queue.h"

class EventSender : public Thread {
private:
	BlockingQueue<Request>& request_queue;
	ServerConnection& server_connection;
public:
	EventSender(BlockingQueue<Request>& request_queue,
							ServerConnection& server_connection);
	~EventSender();
	void run();
};

#endif