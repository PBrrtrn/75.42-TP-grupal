#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <string>

#define TYPE_START_GAME 'n'
#define TYPE_JOIN_GAME 'j'
#define TYPE_MOVE_FORWARD 'w'
#define TYPE_MOVE_BACKWARD 's'
#define TYPE_MOVE_LEFT 'a'
#define TYPE_MOVE_RIGHT 'd'
#define TYPE_EXIT_GAME 'e'
#define TYPE_SHOOT 'l'

class Message {

	private:

		//std::string m;
		int type;
		int entity;
		int value;
		int clientId;	

	public:

		//Message(std::string data,int clientId);
		
		Message(int type,int entity, int value,int clientId);
		
		//std::string getMessage();
		
		int getType();
		int getEntity();
		int getValue();
		
		int getClientId();
		
		~Message();
};

#endif
