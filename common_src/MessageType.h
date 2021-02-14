#ifndef __MESSAGE_TYPE_H__
#define __MESSAGE_TYPE_H__

enum MessageType { 
	//tipos de mensaje desde cliente a servidor
	TYPE_START_GAME = 'n',
	TYPE_JOIN_GAME = 'j',
	TYPE_REFRESH_GAMES_LIST = 'r',
	TYPE_SEND_MAPS_LIST = 'm',
	TYPE_MOVE_FORWARD_START = 'w',
	TYPE_MOVE_BACKWARD_START = 's',
	TYPE_MOVE_LEFT_START = 'a',
	TYPE_MOVE_RIGHT_START = 'd',
	
	TYPE_MOVE_FORWARD_STOP = 'y',
	TYPE_MOVE_BACKWARD_STOP = 'u',
	TYPE_MOVE_LEFT_STOP = 'i',
	TYPE_MOVE_RIGHT_STOP = 'o',	
	
	TYPE_EXIT_GAME = 'e',
	TYPE_SHOOT = 'l',
	TYPE_CHANGE_PISTOLA = '1',
	TYPE_CHANGE_CUCHILLO = '2',
	TYPE_CHANGE_LANZA_COHETES = '3',
	TYPE_CHANGE_AMETRALLADORA = '4',
	TYPE_CHANGE_CANION = '5',
	TYPE_USE_DOOR = 'f',
	TYPE_CLIENT_PING = 'p',
	//tipos de mensaje de respuesta del servidor a cliente
	TYPE_SERVER_SEND_GAME_UPDATE = 1,
	TYPE_SERVER_SEND_GAMES_LIST = 2,
	TYPE_SERVER_SEND_MAP_LIST = 3,
	TYPE_SERVER_SEND_MAP = 4,
	TYPE_SERVER_JOIN_REFUSED = -1,
	TYPE_SERVER_JOIN_OK = 0,
	TYPE_LOBBY_STATUS_UPDATE = 5,
	TYPE_SERVER_SHUTDOWN_CLIENT = 6,
	TYPE_SERVER_SEND_GAME_STATISTICS = 7,
	TYPE_SERVER_NOTHING_TO_REPORT = 10
};

#endif
