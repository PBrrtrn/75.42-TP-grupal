#ifndef __SERVER_CONNECTION_H__
#define __SERVER_CONNECTION_H__

#include "../common_src/Socket.h"
#include "game_status/MenuStatus.h"

class ServerConnection {
private:
	Socket socket;
public:
	ServerConnection();
	~ServerConnection();
	std::vector<GameOption> fetchGameOptions();
};

#endif