#include "EventSender.h"

EventSender::EventSender(BlockingQueue<ClientMessage>& message_queue,
												 ServerConnection& server_connection)
: message_queue(message_queue),	server_connection(server_connection) { }

EventSender::~EventSender() {
	//this->join();
}

void EventSender::shutdown() {
	this->keep_running = false;
}

void EventSender::run() {
	while (this->keep_running) {
		try {
			ClientMessage message = message_queue.pop();
			this->server_connection.sendMessage(message);
		} catch (...) {
			this->shutdown();
		}
	}
}
