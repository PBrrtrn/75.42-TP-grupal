#ifndef __CLIENT_GAME_STATUS_H
#define __CLIENT_GAME_STATUS_H
#include "../../common_src/Vector.h"
#include "./game_status.h"
#include <vector>
#include <algorithm>
#define TOP_STATISTICS 10

//estatus del player asociado a este GameStatus
struct PlayerStatus{
	char clientId;
	Vector position;
	Vector direction;
	char selectedWeapon;
	char health;
	char bullets;
	char lives;
	bool hasKey;
};

//listado de puertas
struct DoorListItem{
	int doorId;
	Vector gridPosition;
	bool isOpen;
};

//listado de Jugadores que no son el player asociado a este GameStatus
struct PlayerListItem {
	char clientId;
	Vector position;
	Vector direction;
	char selectedWeapon;
	bool isAlive;
};

//listado de items asociados a este 
struct ItemListElement {
	char type;
	Vector pos;
	bool isVisible;
};

struct ClientKills {
	char clientId;
	int kills;
};

struct ClientPoints {
	char clientId;
	int puntaje;
};

struct ClientShootedBullets {
	char clientId;
	int bullets_shooted;
};

struct GameStatistics {
	ClientKills kills[TOP_STATISTICS];
	ClientPoints points[TOP_STATISTICS];
	ClientShootedBullets bullets[TOP_STATISTICS];
};

class ClientGameStatus {

	private:
		GameStatus& gameStatus;
		int assignedClientId;

	public:

		ClientGameStatus(GameStatus& gameStatus,int assignedClientId);
		void updateThisGameStatus();
		std::string getEntireMap();
		GameStatistics getStatistics();
		~ClientGameStatus();

		PlayerStatus thisPlayerStatus;
		std::unordered_map<int,PlayerListItem> players; //incluye PlayersPositions y PlayersDirections
		std::unordered_map<int,DoorListItem> doors;
		std::vector<ItemListElement> items;
};

#endif //GAMESTATUS_H
