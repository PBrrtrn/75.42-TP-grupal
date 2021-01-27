#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <string>

#define TYPE_START_GAME 'n'
#define TYPE_JOIN_GAME 'j'
#define TYPE_REFRESH_GAMES_LIST 'r'
#define TYPE_MOVE_FORWARD 'w'
#define TYPE_MOVE_BACKWARD 's'
#define TYPE_MOVE_LEFT 'a'
#define TYPE_MOVE_RIGHT 'd'
#define TYPE_EXIT_GAME 'e'
#define TYPE_SHOOT 'l'
#define TYPE_CHANGE_PISTOLA '1'
#define TYPE_CHANGE_CUCHILLO '2'
#define TYPE_CHANGE_LANZA_COHETES '3'
#define TYPE_CHANGE_AMETRALLADORA '4'
#define TYPE_CHANGE_CANION '5'
#define TYPE_USE_DOOR 'f'

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
