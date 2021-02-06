#ifndef __CLIENT_GAME_STATUS_H
#define __CLIENT_GAME_STATUS_H
#include <vector>
#include "../../common_src/Vector.h"
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

	ClientGameStatus(GameStatus& gameStatus,int assignedClientId): gameStatus(gameStatus){
		this->thisPlayerStatus.clientId = assignedClientId;
		this->thisPlayerStatus.position = this->gameStatus.playersPositions.at(assignedClientId);
		this->thisPlayerStatus.direction = this->gameStatus.playersDirections.at(assignedClientId);
		this->thisPlayerStatus.selectedWeapon = this->gameStatus.players.at(assignedClientId).getSelectedWeaponIndex();
		this->thisPlayerStatus.health = this->gameStatus.players.at(assignedClientId).getHealth();
		this->thisPlayerStatus.bullets = this->gameStatus.players.at(assignedClientId).getCurrentBullets();
		//this->thisPlayerStatus.lives = this->gameStatus.players.at(assignedClientId).getCurrentLives();
		this->thisPlayerStatus.hasKey = this->gameStatus.players.at(assignedClientId).hasKey();
		for (auto& it: this->gameStatus.players) {
			PlayerListItem p;
			p.clientId = it.first;
			p.position = this->gameStatus.playersPositions.at(p.clientId);
			p.direction = this->gameStatus.playersDirections.at(p.clientId);
			p.selectedWeapon = it.second.getSelectedWeaponIndex();
			p.isAlive = it.second.getHealth();
			this->players.push_back(p);
		}
		for (auto& it: this->gameStatus.doors) {
			DoorListItem d;
			d.doorId = it.first;
			d.gridPosition = it.second.getLocation();
			d.isOpen = it.second.isOpen();
			this->doors.push_back(d);
		}	
		
		for (auto& it: this->gameStatus.items) {
			ItemListElement i;
			i.pos = it.getPosition();
			i.isVisible = it.isVisible();
		}		
		
		//std::unordered_map<int, Vector> playersPositions;
		//std::unordered_map<int, Vector> playersDirections;
		//std::unordered_map<int, Player> players;
		//std::unordered_map<int, Door> doors;
		//std::vector<Item> items;
	}
	~ClientGameStatus() {}

	PlayerStatus thisPlayerStatus;
	std::vector<PlayerListItem> players; //incluye PlayersPositions y PlayersDirections
	std::vector<DoorListItem> doors;
	std::vector<ItemListElement> items;
};

#endif //GAMESTATUS_H
