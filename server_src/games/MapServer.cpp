#include "MapServer.h"

MapServer::MapServer(const std::string& file_location): map(file_location.c_str()){
	YAML::Node mapa = YAML::LoadFile(file_location);
	
	this->minPlayers = mapa["minPlayers"].as<int>();
	this->maxPlayers = mapa["maxPlayers"].as<int>();
	
	
	if (mapa["items"]){
		this->items_yml = mapa["items"].as<std::vector<std::string>>();
		this->loadItems();
	}
	if (mapa["doors"]){
		this->doors_yml = mapa["doors"].as<std::vector<std::string>>();
		this->loadDoors();
	}
	if(mapa["spawnpoints"]) {
		this->spawnpoints_yml = mapa["spawnpoints"].as<std::vector<std::string>>();
		this->loadSpawnPoints();
	}
	
}

MapServer::MapServer(MapServer&& from){
	this->map = from.map;
	this->minPlayers = from.minPlayers;
	this->maxPlayers = from.maxPlayers;
	
	this->items = from.items;
	this->respawnPoints = from.respawnPoints;
	this->doors = from.doors;
	from.items = std::vector<Item*>();
}

void MapServer::loadItems(){
	for (std::vector<std::string>::iterator it = this->items_yml.begin() ; it != this->items_yml.end(); ++it) {
		Item* item = this->item_serializer.deserialize(*it);
		this->items.push_back(item);
		
	}	
}

void MapServer::loadDoors(){
	for (std::vector<std::string>::iterator it = this->doors_yml.begin() ; it != this->doors_yml.end(); ++it) {
		this->doors.push_back(this->door_serializer.deserialize(*it));
	}
}

void MapServer::loadSpawnPoints() {
	for (std::vector<std::string>::iterator it = this->spawnpoints_yml.begin() ; it != this->spawnpoints_yml.end(); ++it) {
		this->respawnPoints.push_back(this->spawnpoints_serializer.deserialize(*it));
	}	
}

std::vector<int>& MapServer::operator[](int x) {
	return this->map[x];
}

int MapServer::getMaxPlayers() {
	return this->maxPlayers;
}

int MapServer::getMinPlayers() {
	return this->minPlayers;
}

int MapServer::getGridValue(int x, int y) {
	return this->map.getGridValue(x,y);
}

int MapServer::isWall(int x, int y) {
	return (this->map.getGridValue(x,y) > 0);
}

bool MapServer::isObstacle(Vector position) {
	for (std::vector<Item*>::iterator it = this->items.begin() ; it != this->items.end(); ++it) {
		if ((*it)->getPosition() == position) return true;
	}
	for (std::vector<Door>::iterator it = this->doors.begin() ; it != this->doors.end(); ++it) {
		if ((*it).getLocation() == position && (*it).isLocked()) return true;
	}
	return false;
}

int MapServer::getWidth() {
	return this->map.getWidth();
}

int MapServer::getHeight() {
	return this->map.getHeight();
}

std::vector<Item*>& MapServer::getItems() { 
	return this->items;
}
std::vector<Door>& MapServer::getDoors() { 
	return this->doors;
}
std::vector<SpawnPoint>& MapServer::getRespawnPoints() { 
	return this->respawnPoints;
}

Map& MapServer::getMap() {
	return this->map;
}

std::string MapServer::getSerializedMap() {
	std::string serializedMap = this->map.getSerializedMap();
	std::vector<std::string> serializedItems;
	std::vector<std::string> serializedRespawns;
	
	ItemSerializer itemSerializer;
	SpawnPointSerializer respawnSerializer;
	
	for (auto it: this->items) {
		std::string itemSerialized = itemSerializer.serialize(it);
		serializedItems.push_back(itemSerialized);
    }
	for (auto& it: this->respawnPoints) {
		std::string respawn = respawnSerializer.serialize(it);
		serializedRespawns.push_back(respawn);
    }	
    YAML::Emitter outMap;
    
    outMap << YAML::BeginMap;
		outMap << YAML::Key << "minPlayers";
		outMap << YAML::Value << this->minPlayers ;	
		outMap << YAML::Key << "maxPlayers";
		outMap << YAML::Value << this->maxPlayers ;	
		
		outMap << YAML::Key << "items";
		outMap << YAML::Value << YAML::Flow << serializedItems;		
		
		outMap << YAML::Key << "spawnpoints";
		outMap << YAML::Value << YAML::Flow << serializedRespawns;	

	outMap << YAML::EndMap;
	
	
	return std::string(outMap.c_str()) + '\n' + serializedMap;
}

MapServer::MapServer(int width,int height,int minPlayers,int maxPlayers) : map(width,height){
	this->minPlayers = minPlayers;
	this->maxPlayers = maxPlayers;
}

void MapServer::setGridValue(int x, int y,int newValue) {
	this->map.setGridValue(x,y,newValue);
}

MapServer::~MapServer() { 
	for (auto x : this->items) {
		delete x;
	}
}

void MapServer::insertItem(Item* item){
	this->items.push_back(item);
}

void MapServer::insertSpawnPoint(SpawnPoint s){
	this->respawnPoints.push_back(s);
}
