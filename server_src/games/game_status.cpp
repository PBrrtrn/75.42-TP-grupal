#include "game_status.h"

GameStatus::GameStatus(std::string mapLocation) : map(mapLocation) {
	this->mapLocation = mapLocation;
	
	File mapaArchivo(mapLocation.c_str());
	
	while (mapaArchivo.hasLine()) {
		this->entireMap += mapaArchivo.getLine() + '\n';
	}
	
	this->loadDoors();

	const YAML::Node& c = ServerConfig::Config["Item"];

    this->itemPickUpRange = c["PickUpRange"].as<float>();
	
}

std::vector<SpawnPoint> GameStatus::getSpawnPoints() {
	return this->map.getRespawnPoints();
}

void GameStatus::loadDoors() {
	std::vector<Door> map_doors = this->map.getDoors();
	int doors_amount = 0;
	for (std::vector<Door>::iterator it = map_doors.begin() ; it != map_doors.end(); ++it) {
		this->doors.insert({doors_amount, (*it)});
		doors_amount++;
	}
}

void GameStatus::setPosition(int playerID, float pos_x, float pos_y) {
    this->playersPositions[playerID] = Vector(pos_x, pos_y);
}

void GameStatus::setPosition(int playerID, Vector &playerPosition) {
    this->playersPositions[playerID] = playerPosition;
}

void GameStatus::setAngle(int playerID, float angle) {
	this->playersDirections[playerID] = Vector(angle);
}

Vector GameStatus::getPosition(int playerID) {
	return this->playersPositions[playerID];
}

int GameStatus::getMaxPlayers() {
	return this->map.getMaxPlayers();
}

int GameStatus::getMinPlayers() {
	return this->map.getMinPlayers();
}

void GameStatus::addPlayer(int playerID, Vector &position, Vector &direction) {
    this->playersPositions[playerID] = position;
    this->playersDirections[playerID] = direction;

    Player jugador(playerID);
	this->players.insert({playerID, std::move(jugador)});
	this->respawn_events.insert(std::make_pair(
		playerID, 
		new RespawnEvent(&this->players.at(playerID), &Player::respawn)
	));
}

float GameStatus::getAngle(int playerID) {
    return this->playersDirections[playerID].getAngle();
}


Vector GameStatus::getDirection(int playerID) {
    return this->playersDirections[playerID];
}

void GameStatus::checkPlayerPickups(){
	for (auto item: this->map.getItems()) {
		Vector item_position = item->getPosition();

        for (auto& it: this->players){
			int player_id = it.first;
			Player& player = it.second;
			if (!player.outGame()){
				Vector distance = item_position - this->getPosition(player_id);
				if (abs(distance.norm()) < this->itemPickUpRange && item->canBePickedUp()) {
					item->pickUp(player);
				}			
			}
		}
        
    }
	for (auto item: this->items) {
		Vector item_position = item->getPosition();

        for (auto& it: this->players){
			int player_id = it.first;
			Player& player = it.second;
			if (!player.outGame()){
				Vector distance = item_position - this->getPosition(player_id);
				if (abs(distance.norm()) < this->itemPickUpRange && item->canBePickedUp()) {
					item->pickUp(player);
				}
			}		
		}
        
    }
}

void GameStatus::checkPlayerBullets(){
	for (auto& it: this->players){
		int player_id = it.first;
		Player& player = it.second;

		if (player.getCurrentBullets() == 0) {
			player.changeWeapon(0);
		}		
	}	
	
}

void GameStatus::updateRespawnEvents(double delta) {
	for (auto te: this->respawn_events) {
    	if (te.second->update(delta)) {
			std::vector<SpawnPoint> spawnpoints = this->getSpawnPoints();
			int sp_idx = rand()% (spawnpoints.size());
			Vector position = spawnpoints[sp_idx].getPosition();
			this->setPosition(te.first, position);
			te.second->deactivate();
		}
  	} 
}

int GameStatus::getAlivePlayers() {
	int amount_alive = 0;
	for (auto& it: this->players){
		int player_id = it.first;
		Player& player = it.second;
		if (!player.is_dead()) amount_alive++;
	}	
	return amount_alive;
}

Statistics& GameStatus::showStatistics() {
	for (auto& it: this->players){
		int player_id = it.first;
		Player& player = it.second;
		this->statistics.addPointsTreasure(player_id, player.getPoints());	
	}	
	return this->statistics;
}

void GameStatus::addEnemyDead(int playerID) {
	this->statistics.addEnemyDead(playerID);
}

void GameStatus::addBulletShooted(int playerID) {
	this->statistics.addBulletShooted(playerID);
}

void GameStatus::respawnItems(){
	for (auto it: this->map.getItems()){
		it->tick();
	}
	for (auto it: this->items){
		it->tick();
	}
}

std::string GameStatus::getEntireMap(){
	return this->entireMap;
}

float GameStatus::getShootTimeout(int playerID) {
	return this->players.at(playerID).getShootTimeout();
}

bool GameStatus::changeMovementState(int clientId,MovementState state){
	return this->players.at(clientId).changeMovementState(state);
	
}

std::vector<Item*>& GameStatus::getMapItems() {
	return this->map.getItems();
}

std::vector<Item*>& GameStatus::getGsItems() {
	return this->items;
}

bool GameStatus::changeShootingState(int clientId,ShootingState state){
	return this->players.at(clientId).changeShootingState(state);
	
}

bool GameStatus::changeRotationState(int clientId,MovementState state){
	return this->players.at(clientId).changeRotationState(state);
}

bool GameStatus::changeFiringState(int clientId, FiringState state) {
	return this->players.at(clientId).changeFiringState(state);
}

std::unordered_map<int,MovementState> GameStatus::getPlayerMovementStates(){
	std::unordered_map<int,MovementState> states;
	for (auto& p: this->players){
		if (p.second.getCurrentMovementState() != STATE_NOT_MOVING){
			states.insert({p.first,p.second.getCurrentMovementState()});
		}
	}
	return states;		
}

std::unordered_map<int,MovementState> GameStatus::getPlayerRotationStates(){
	std::unordered_map<int,MovementState> states;
	for (auto& p: this->players){
		if (p.second.getCurrentRotationState() != STATE_NOT_MOVING){
			states.insert({p.first,p.second.getCurrentRotationState()});
		}
	}
	return states;		
}

Map& GameStatus::getMap() {
	return this->map.getMap();
}

void GameStatus::resetPlayerStatusEvents() {
	for (auto& p: this->players) {
    	p.second.resetStepEvents();
  	}
}

bool GameStatus::isPlayer(Vector& position) {
	for (auto& p: this->playersPositions) {
    	if (p.second == position) return true; 
  	}
	return false;
}

int* GameStatus::getMapGrid(){
	return this->map.getMapGridCopy();
}
int GameStatus::getMapWidth(){
	return this->map.getWidth();
	
}
int GameStatus::getMapHeight(){
	return this->map.getHeight();
	
}

GameStatus::~GameStatus() {
	for (auto x : this->items) {
		delete x;
	}
	for (auto x : this->respawn_events) {
    	delete x.second;
  	}
}
