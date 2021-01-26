#include "message.h"

Message::Message(int t,int e, int v, int clientId) : type(t), entity(e), value(v) ,clientId(clientId){}

//std::string Message::getMessage(){
//	return this->m;
//}
int Message::getClientId(){
	return this->clientId;
}

int Message::getType(){
	return this->type;
}
int Message::getEntity(){
	return this->entity;
}
int Message::getValue(){
	return this->value;
}

Message::~Message(){}
