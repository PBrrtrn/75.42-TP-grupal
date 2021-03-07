#ifndef __CLIENT_GAME_STATUS_H
#define __CLIENT_GAME_STATUS_H
#include "./game_status.h"
#include "../../common_src/ClientGameStatusElements.h"
#include <vector>
#include <algorithm>

class ClientGameStatus {

	private:
		GameStatus& gameStatus;
		int assignedClientId;

	public:

		ClientGameStatus(GameStatus& gameStatus,int assignedClientId);
		void updateThisGameStatus();
		std::string getEntireMap();
		int* getMapGrid();
		int getMapWidth();
		int getMapHeight();
		GameStatistics getStatistics();
		~ClientGameStatus();

		PlayerStatus thisPlayerStatus;
		std::unordered_map<int,PlayerListItem> players; //incluye PlayersPositions y PlayersDirections
		std::unordered_map<int,DoorListItem> doors;
		std::vector<ItemListElement> items;
};

#endif //GAMESTATUS_H
