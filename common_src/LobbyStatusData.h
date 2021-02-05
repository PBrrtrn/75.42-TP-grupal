#ifndef __LOBBY_STATUS_DATA_H_
#define __LOBBY_STATUS_DATA_H_

struct LobbyStatusData {
	int remainingTime;
	int players;
	int maxPlayers;
	bool gameStarted;
};

#endif
