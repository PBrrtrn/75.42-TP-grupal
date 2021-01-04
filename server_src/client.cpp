#include "client.h"

Client::Client() : server(send_queue) {}

Client::~Client(){
	this->send_queue.close();
}

void Client::startGame() {
    this->server.start();

    this->send_queue.push("w");
    this->send_queue.push("a");
    this->send_queue.push("s");
    this->send_queue.push("d");
    this->send_queue.push("a");
    this->send_queue.push("s");
    this->send_queue.push("w");
}
