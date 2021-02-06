#include "./client_game_status.h"

ClientGameStatus::ClientGameStatus(GameStatus& gameStatus, int assignedClientId): gameStatus(gameStatus), assignedClientId(assignedClientId){
	this->updateThisGameStatus();
}

void ClientGameStatus::updateThisGameStatus(){
		this->thisPlayerStatus.clientId = assignedClientId;
		this->thisPlayerStatus.position = this->gameStatus.playersPositions.at(assignedClientId);
		this->thisPlayerStatus.direction = this->gameStatus.playersDirections.at(assignedClientId);
		this->thisPlayerStatus.selectedWeapon = this->gameStatus.players.at(assignedClientId).getSelectedWeaponIndex();
		this->thisPlayerStatus.health = this->gameStatus.players.at(assignedClientId).getHealth();
		this->thisPlayerStatus.bullets = this->gameStatus.players.at(assignedClientId).getCurrentBullets();
		this->thisPlayerStatus.lives = this->gameStatus.players.at(assignedClientId).getLives();
		this->thisPlayerStatus.hasKey = this->gameStatus.players.at(assignedClientId).hasKey();
		for (auto& it: this->gameStatus.players) {
			if (this->players.find(it.first) == this->players.end()) {
				PlayerListItem p;
				p.clientId = it.first;
				p.position = this->gameStatus.playersPositions.at(p.clientId);
				p.direction = this->gameStatus.playersDirections.at(p.clientId);
				p.selectedWeapon = it.second.getSelectedWeaponIndex();
				p.isAlive = it.second.getHealth();
				this->players.insert({it.first,p});
			} else {
				this->players.at(it.first).clientId = it.first;
				this->players.at(it.first).position = this->gameStatus.playersPositions.at(it.first);
				this->players.at(it.first).direction = this->gameStatus.playersDirections.at(it.first);
				this->players.at(it.first).selectedWeapon = it.second.getSelectedWeaponIndex();
				this->players.at(it.first).isAlive = it.second.getHealth() ? true : false;				
			}
		}
		for (auto& it: this->gameStatus.doors) {
			if (this->doors.find(it.first) == this->doors.end()) {
				DoorListItem d;
				d.doorId = it.first;
				d.gridPosition = it.second.getLocation();
				d.isOpen = it.second.isOpen();
				this->doors.insert({it.first,d});
			} else {
				this->doors.at(it.first).doorId = it.first;
				this->doors.at(it.first).gridPosition = it.second.getLocation();
				this->doors.at(it.first).isOpen = it.second.isOpen();				
			}
		}	
		
		for (auto& it: this->gameStatus.items) {
			ItemListElement i;
			i.pos = it.getPosition();
			i.isVisible = it.isVisible();
			this->items.push_back(i);
		}	
}

ClientGameStatus::~ClientGameStatus() {}
