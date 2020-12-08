#include "ServerEventsReceiver.h"

ServerEventsReceiver::ServerEventsReceiver() { }

ServerEventsReceiver::~ServerEventsReceiver() {
	this->join();
}

void ServerEventsReceiver::run() { }
