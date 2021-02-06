#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <string>

#define TYPE_START_GAME 'n'
#define TYPE_JOIN_GAME 'j'
#define TYPE_REFRESH_GAMES_LIST 'r'
#define TYPE_SEND_MAPS_LIST 'm'
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

#define TYPE_SERVER_SEND_GAME_UPDATE 1
#define TYPE_SERVER_SEND_GAMES_LIST 2
#define TYPE_SERVER_SEND_MAP_LIST 3
#define TYPE_SERVER_SEND_MAP 4
#define TYPE_SERVER_JOIN_REFUSED -1
#define TYPE_SERVER_JOIN_OK 0
#define TYPE_LOBBY_STATUS_UPDATE 5
#define TYPE_SERVER_SHUTDOWN_CLIENT 6

class Message {

	private:
		int type;
		int entity;
		int clientId;	

	public:
		
		Message(int type,int entity,int clientId);
		
		int getType();
		int getEntity();
		int getClientId();
		
		~Message();
};

#endif
