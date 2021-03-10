#include "EventSender.h"

EventSender::EventSender(BlockingQueue<ClientMessage>& message_queue,
												 ServerConnection& server_connection)
: message_queue(message_queue),	server_connection(server_connection) { }

EventSender::~EventSender() {
	this->join();
}

void EventSender::run() {
	while (true) {
		ClientMessage message = message_queue.pop();
		this->server_connection.sendMessage(message);
	}
}
