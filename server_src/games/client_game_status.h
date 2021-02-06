#ifndef __CLIENT_GAME_STATUS_H
#define __CLIENT_GAME_STATUS_H
#include <vector>
#include "../../common_src/Vector.h"
#include "./game_status.h"
#include <vector>

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
	Vector pos;
	bool isVisible;
};

class ClientGameStatus {

	private:
		GameStatus& gameStatus;

	public:

		ClientGameStatus(GameStatus& gameStatus,int assignedClientId);
		~ClientGameStatus();

		PlayerStatus thisPlayerStatus;
		std::vector<PlayerListItem> players; //incluye PlayersPositions y PlayersDirections
		std::vector<DoorListItem> doors;
		std::vector<ItemListElement> items;
};

#endif //GAMESTATUS_H
