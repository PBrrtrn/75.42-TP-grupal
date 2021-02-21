#include "EventSender.h"

EventSender::EventSender(std::atomic<bool>& in_game, 
												 BlockingQueue<Request>& request_queue,
												 ServerConnection& server_connection)
: in_game(in_game), request_queue(request_queue), 
	server_connection(server_connection) { }

EventSender::~EventSender() {
	this->join();
}

void EventSender::run() {
	while (true) {
		Request request = request_queue.pop();
		this->server_connection.sendRequest(request);
	}
}
