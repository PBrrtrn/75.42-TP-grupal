#ifndef __MESSAGE_TYPE_H__
#define __MESSAGE_TYPE_H__

enum MessageType { 
	// tipos de mensaje de pedido del cliente al servidor
	CLIENT_REQUEST_MAPS_LIST,
	CLIENT_REQUEST_GAMES_LIST,
	CLIENT_REQUEST_CREATE_GAME,
	CLIENT_REQUEST_JOIN_GAME,
	CLIENT_REQUEST_LEAVE_GAME,
	//tipos de mensaje desde cliente a servidor
	TYPE_UNDEFINED_KEY,

	// TYPE_START_GAME,
	// TYPE_JOIN_GAME,
	// TYPE_REFRESH_GAMES_LIST,
	// TYPE_SEND_MAPS_LIST,
	// TYPE_EXIT_GAME,
	TYPE_MOVE_FORWARD_START,
	TYPE_MOVE_BACKWARD_START,
	TYPE_MOVE_LEFT_START,
	TYPE_MOVE_RIGHT_START,
	
	TYPE_MOVE_FORWARD_STOP,
	TYPE_MOVE_BACKWARD_STOP,
	TYPE_MOVE_LEFT_STOP,
	TYPE_MOVE_RIGHT_STOP,	
	
	TYPE_SHOOT_STOP,
	TYPE_SHOOT_START,

	TYPE_CHANGE_PISTOLA,
	TYPE_CHANGE_CUCHILLO,
	TYPE_CHANGE_LANZA_COHETES,
	TYPE_CHANGE_AMETRALLADORA,
	TYPE_CHANGE_CANION,
	TYPE_USE_DOOR,

	TYPE_CLIENT_PING,
	// tipos de mensaje de respuesta del servidor a cliente
	TYPE_SERVER_SEND_GAME_UPDATE,
	TYPE_SERVER_SEND_GAMES_LIST,
	TYPE_SERVER_SEND_MAP_LIST,
	TYPE_SERVER_SEND_MAP,
	TYPE_SERVER_JOIN_REFUSED,
	TYPE_SERVER_JOIN_OK,
	TYPE_LOBBY_STATUS_UPDATE,
	TYPE_SERVER_SHUTDOWN_CLIENT,
	TYPE_SERVER_SEND_GAME_STATISTICS,
	TYPE_SERVER_NOTHING_TO_REPORT
};

#endif
