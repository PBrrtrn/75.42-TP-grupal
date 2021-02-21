#ifndef __SERVER_CONNECTION_H__
#define __SERVER_CONNECTION_H__

#include <string>
#include <vector>

#include "../common_src/Socket.h"
#include "../common_src/MapListItem.h"
#include "../common_src/GameListItem.h"
#include "../common_src/MessageType.h"
#include "../common_src/LobbyStatusData.h"
#include "game_status/GameStatus.h"

class ServerConnection {
private:
	Socket socket;
	char client_id;
public:
	ServerConnection(std::string host, std::string service);
	~ServerConnection();
	MessageType receiveMessageType();
	std::vector<MapListItem> getMapOptions();
	std::vector<GameListItem> getGameOptions();
	LobbyStatusData getLobbyStatus();
	Map getMap();
	GameStatusUpdate getGameStatusUpdate();
	GameStatistics getGameStatistics();
	/*
	bool joinGame(char game_id);
	void exitLobby();
	void sendEvents(std::vector<MessageType> events);
	void sendPing();
	*/
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
