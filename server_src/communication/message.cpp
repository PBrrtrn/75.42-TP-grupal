#include "message.h"

Message::Message(std::string data,int clientId) : m(data),clientId(clientId){}

std::string Message::getMessage(){
	return this->m;
}
int Message::getClientId(){
	return this->clientId;
}

Message::~Message(){}
