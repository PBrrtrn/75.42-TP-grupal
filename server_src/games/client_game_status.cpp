#include "./client_game_status.h"

static bool comp(std::pair<int, int>& a,
         std::pair<int, int>& b)
{
    return a.second < b.second;
}

ClientGameStatus::ClientGameStatus(GameStatus& gameStatus, int assignedClientId): gameStatus(gameStatus), assignedClientId(assignedClientId){
	this->updateThisGameStatus();
}

void ClientGameStatus::updateThisGameStatus(){
		// this->thisPlayerStatus.clientId = assignedClientId;
		this->thisPlayerStatus.position = this->gameStatus.playersPositions.at(assignedClientId);
		this->thisPlayerStatus.direction = this->gameStatus.playersDirections.at(assignedClientId);
		this->thisPlayerStatus.selectedWeapon = this->gameStatus.players.at(assignedClientId).getSelectedWeaponIndex();
		this->thisPlayerStatus.health = this->gameStatus.players.at(assignedClientId).getHealth();
		this->thisPlayerStatus.bullets = this->gameStatus.players.at(assignedClientId).getCurrentBullets();
		this->thisPlayerStatus.lives = this->gameStatus.players.at(assignedClientId).getLives();
		this->thisPlayerStatus.hasKey = this->gameStatus.players.at(assignedClientId).hasKey();
		this->thisPlayerStatus.firing_state = this->gameStatus.players.at(assignedClientId).getCurrentFiringState();
		this->thisPlayerStatus.receivedDamage = this->gameStatus.players.at(assignedClientId).receivedDamageInStep();
		this->thisPlayerStatus.died = this->gameStatus.players.at(assignedClientId).diedInStep();
		this->thisPlayerStatus.pickedUpTreasure = this->gameStatus.players.at(assignedClientId).pickedUpTreasureInStep();
		this->thisPlayerStatus.pickedUpBullets = this->gameStatus.players.at(assignedClientId).pickedUpBulletsInStep();
		this->thisPlayerStatus.pickedUpLife = this->gameStatus.players.at(assignedClientId).pickedUpLifeInStep();
		this->thisPlayerStatus.before_respawn = this->gameStatus.players.at(assignedClientId).outGame();
		for (auto& it: this->gameStatus.players) {
			if (this->players.find(it.first) == this->players.end()) {
				PlayerListItem p;
				memset(&p, 0, sizeof(PlayerListItem));
				p.clientId = it.first;
				p.position = this->gameStatus.playersPositions.at(p.clientId);
				p.direction = this->gameStatus.playersDirections.at(p.clientId);
				p.selectedWeapon = it.second.getSelectedWeaponIndex();
				p.isAlive = it.second.getHealth();
				p.receiveDamage = it.second.receivedDamageInStep();
				p.firing_state = it.second.isShooting();
				p.movement_state = it.second.isMoving();
				p.before_respawn = it.second.outGame();
				p.died = it.second.diedInStep();
				this->players.insert({it.first,p});
			} else {
				this->players.at(it.first).clientId = it.first;
				this->players.at(it.first).position = this->gameStatus.playersPositions.at(it.first);
				this->players.at(it.first).direction = this->gameStatus.playersDirections.at(it.first);
				this->players.at(it.first).selectedWeapon = it.second.getSelectedWeaponIndex();
				this->players.at(it.first).isAlive = it.second.getHealth() ? true : false;
				this->players.at(it.first).receiveDamage = it.second.receivedDamageInStep();
				this->players.at(it.first).firing_state = it.second.isShooting();
				this->players.at(it.first).movement_state = it.second.isMoving();
				this->players.at(it.first).before_respawn = it.second.outGame();	
				this->players.at(it.first).died = it.second.diedInStep();			
			}
		}
		for (auto& it: this->gameStatus.doors) {
			if (this->doors.find(it.first) == this->doors.end()) {
				DoorListItem d;
				memset(&d, 0, sizeof(DoorListItem));
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
		
		this->items.clear();

		for (auto& it: this->gameStatus.getGsItems()) {
			if (it->isVisible()) {
				ItemListElement i;
				memset(&i, 0, sizeof(ItemListElement));
				i.type = it->getType();
				i.pos = it->getPosition();
				this->items.push_back(i);
			}
		}	

		for (auto& it: this->gameStatus.getMapItems()) {
			if (it->isVisible()) {
				ItemListElement i;
				memset(&i, 0, sizeof(ItemListElement));
				i.type = it->getType();
				i.pos = it->getPosition();
				this->items.push_back(i);
			}
		}
}

std::string ClientGameStatus::getEntireMap(){
	return this->gameStatus.getEntireMap();
}

GameStatistics ClientGameStatus::getStatistics() {
	GameStatistics gs;
	memset(&gs, 0, sizeof(GameStatistics));

	Statistics& s = this->gameStatus.showStatistics();

	std::unordered_map<int, int> kills = s.getEnemysDead();
	ClientKills gs_kills;
	memset(&gs_kills, 0, sizeof(ClientKills));
	int top = 0;
	for (auto k: kills) {
		if (top >= TOP_STATISTICS) break;
		std::cout << "id" << k.first << std::endl;
		gs_kills.clientId = k.first;
		std::cout << "kills" << k.second << std::endl;
		gs_kills.kills = k.second;
		gs.kills[top] = gs_kills;
		top++;
	}

	std::unordered_map<int, int> points = s.getPointsGame();
	ClientPoints gs_points;
	memset(&gs_points, 0, sizeof(ClientPoints));
	top = 0;
	for (auto p: points) {
		if (top >= TOP_STATISTICS) break;
		std::cout << "id" << p.first << std::endl;
		gs_points.clientId = p.first;
		std::cout << "puntaje" << p.second << std::endl;
		gs_points.puntaje = p.second;
		gs.points[top] = gs_points;
		top++;
	}

	std::unordered_map<int, int> bullets = s.getBulletsShot();
	ClientShootedBullets gs_bullets;
	memset(&gs_bullets, 0, sizeof(ClientShootedBullets));
	top = 0;
	for (auto b: points) {
		if (top >= TOP_STATISTICS) break;
		std::cout << "id" << b.first << std::endl;
		gs_bullets.clientId = b.first;
		std::cout << "bullets" << b.second << std::endl;
		gs_bullets.bullets_shooted = b.second;
		gs.bullets[top] = gs_bullets;
		top++;
	}

	/*
	std::vector<std::pair<int, int>> kills(s.getEnemysDead().begin(), s.getEnemysDead().end());
	std::sort(kills.begin(), kills.end(), comp);

	std::vector<std::pair<int, int>> points(s.getPointsGame().begin(), s.getPointsGame().end());
	std::sort(points.begin(), points.end(), comp);

	std::vector<std::pair<int, int>> bullets(s.getBulletsShot().begin(), s.getBulletsShot().end());
	std::sort(bullets.begin(), bullets.end(), comp);

	for (int i = 0; i < TOP_STATISTICS; i++) {
		if (i < kills.size()) {
			ClientKills gs_kills;
			memset(&gs_kills, 0, sizeof(ClientKills));
			gs_kills.clientId = kills[i].first;
			gs_kills.kills = kills[i].second;
			gs.kills[i] = gs_kills;
		}
		
		if (i < points.size()) {
			ClientPoints gs_points;
			memset(&gs_points, 0, sizeof(ClientPoints));
			gs_points.clientId = points[i].first;
			gs_points.puntaje = points[i].second;
			gs.points[i] = gs_points;
		}

		if (i < kills.size()) {
			ClientShootedBullets gs_bullets;
			memset(&gs_bullets, 0, sizeof(ClientShootedBullets));
			gs_bullets.clientId = bullets[i].first;
			gs_bullets.bullets_shooted = bullets[i].second;
			gs.bullets[i] = gs_bullets;
		}

	}
	*/
	
	return gs;
}

int* ClientGameStatus::getMapGrid(){
	return this->gameStatus.getMapGrid();
}

int ClientGameStatus::getMapWidth(){
	return this->gameStatus.getMapWidth();
}

int ClientGameStatus::getMapHeight(){
	return this->gameStatus.getMapHeight();
}


ClientGameStatus::~ClientGameStatus() {}
