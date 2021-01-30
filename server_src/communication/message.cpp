#include "message.h"

Message::Message(int t,int e, int clientId) : type(t), entity(e), clientId(clientId){}

int Message::getClientId(){
	return this->clientId;
}

int Message::getType(){
	return this->type;
}
int Message::getEntity(){
	return this->entity;
}
Message::~Message(){}
