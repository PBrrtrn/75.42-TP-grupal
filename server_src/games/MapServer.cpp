#include "MapServer.h"

//MapServer::MapServer(const char* file_location) {
	
	//YAML::Node mapa = YAML::LoadFile(std::string(file_location));
	
	//this->width = mapa["width"].as<int>();
	//this->height = mapa["height"].as<int>();	
	//this->grid = mapa["grid"].as<std::vector<std::vector<int>>>();
//}

MapServer::MapServer(const std::string& file_location): map(file_location.c_str()){
	
	YAML::Node mapa = YAML::LoadFile(file_location);
	
	this->minPlayers = mapa["minPlayers"].as<int>();
	this->maxPlayers = mapa["maxPlayers"].as<int>();
	
	//TODO: levantar de YML
	this->items.push_back(Food(Vector(10,10),true));
	this->doors.push_back(Door(false,5,4));
	this->respawnPoints.push_back(SpawnPoint(Vector(6,6),Vector(1,0)));
	this->respawnPoints.push_back(SpawnPoint(Vector(11,6),Vector(1,0)));	
	
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
std::vector<Door> MapServer::getDoor() { 
	return this->doors;
}
std::vector<SpawnPoint> MapServer::getRespawnPoints() { 
	return this->respawnPoints;
}
