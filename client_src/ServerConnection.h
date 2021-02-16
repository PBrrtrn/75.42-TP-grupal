#ifndef __SERVER_CONNECTION_H__
#define __SERVER_CONNECTION_H__

#include <string>
#include <mutex>
#include <vector>

#include "../common_src/Socket.h"
#include "../common_src/MapListItem.h"
#include "../common_src/GameListItem.h"
#include "../common_src/MessageType.h"
#include "../common_src/LobbyStatusData.h"
#include "game_status/GameStatus.h"
#include <condition_variable>

class ServerConnection {
private:
	Socket socket;
	char client_id;
	std::mutex mutex;
	bool receiving;
	std::condition_variable cv;
public:
	ServerConnection(std::string host, std::string service);
	~ServerConnection();
	std::vector<MapListItem> fetchAvailableMaps();
	std::vector<GameListItem> fetchGameOptions();
	bool joinGame(char game_id);
	LobbyStatusData fetchLobbyStatus();
	void exitLobby();
	Map fetchMap();
	void sendEvents(std::vector<MessageType> events);
	GameStatusUpdate fetchGameStatusUpdate();
	GameStatistics receiveStatistics();
	MessageType receiveIncomingEvent();
	void sendPing();
};

#define ERROR_BUF_LEN 256

class ServerConnectionError : public std::exception {
private:
	char error_msg[ERROR_BUF_LEN];
public:
	explicit ServerConnectionError(const char* error) noexcept;
  virtual const char* what() const noexcept;
  virtual ~ServerConnectionError() noexcept;
};

#endif
