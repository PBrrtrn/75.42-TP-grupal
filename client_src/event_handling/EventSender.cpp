#include "EventSender.h"

EventSender::EventSender(BlockingQueue<ClientMessage>& message_queue,
												 ServerConnection& server_connection)
: message_queue(message_queue),	server_connection(server_connection),
	running(true) { }

EventSender::~EventSender() {
	this->join();
}

void EventSender::run() {
	while (this->running) {
		ClientMessage message = message_queue.pop();
		this->server_connection.sendMessage(message);
	}
}

void EventSender::stop() {
	this->running = false;
}