#ifndef __LOBBY_STATUS_H_
#define __LOBBY_STATUS_H_

struct LobbyStatus{
	uint8_t players;
	uint8_t maxPlayers;
	uint8_t remainingTime;
	bool gameStarted;
};

#endif
