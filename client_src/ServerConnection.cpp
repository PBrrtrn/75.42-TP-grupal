#include "ServerConnection.h"

ServerConnection::ServerConnection() { }

ServerConnection::~ServerConnection() { }

std::vector<GameOption> ServerConnection::fetchGameOptions() {
	std::vector<GameOption> options;

	GameOption game_option { std::string("Mapin el mapa"), 4, 1 };
	options.push_back(game_option);

	return options;
}
