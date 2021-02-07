#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <string>
#include "../../common_src/MessageType.h"

class Message {

	private:
		MessageType type;
		int entity;
		int clientId;	

	public:
		
		Message(MessageType type,int entity,int clientId);
		
		int getType();
		int getEntity();
		int getClientId();
		
		~Message();
};

#endif
