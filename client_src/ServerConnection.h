#ifndef __SERVER_CONNECTION_H__
#define __SERVER_CONNECTION_H__

#include <string>
#include <mutex>

#include "../common_src/Socket.h"
#include "game_status/MenuStatus.h"

class ServerConnection {
private:
	Socket socket;
	int client_id;
	std::mutex mutex;
public:
	ServerConnection(std::string host, std::string service);
	~ServerConnection();
	std::vector<GameOption> fetchGameOptions();
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