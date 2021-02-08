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
	
}

void MapServer::loadItems(){
	for (std::vector<std::string>::iterator it = this->items_yml.begin() ; it != this->items_yml.end(); ++it) {
		this->items.push_back(this->item_serializer.deserialize(*it));
	}
}

void MapServer::loadDoors(){
	for (std::vector<std::string>::iterator it = this->doors_yml.begin() ; it != this->doors_yml.end(); ++it) {
		this->doors.push_back(this->door_serializer.deserialize(*it));
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

int MapServer::getWidth() {
	return this->map.getWidth();
}

int MapServer::getHeight() {
	return this->map.getHeight();
}

MapServer::~MapServer() { }

std::vector<Item> MapServer::getItems() { 
	return this->items;
}
std::vector<Door> MapServer::getDoors() { 
	return this->doors;
}
std::vector<SpawnPoint> MapServer::getRespawnPoints() { 
	return this->respawnPoints;
}
