#include <iostream>
#include <sstream>
#include <fstream>

#include "Map.h"
#include "File.h"

Map::Map() { }

Map::Map(const char* file_location) {
	
	YAML::Node mapa = YAML::LoadFile(std::string(file_location));
	
	this->width = mapa["width"].as<int>();
	this->height = mapa["height"].as<int>();	
	this->grid = mapa["grid"].as<std::vector<std::vector<int>>>();
	this->minPlayers = mapa["minPlayers"].as<int>();
	this->maxPlayers = mapa["maxPlayers"].as<int>();
}

Map::Map(const std::string& file_location): Map(file_location.c_str()){ }

std::vector<int>& Map::operator[](int x) {
	return this->grid[x];
}

int Map::getMaxPlayers() {
	return this->maxPlayers;
}

int Map::getMinPlayers() {
	return this->minPlayers;
}

int Map::getGridValue(int x, int y) {
	return this->grid[x][y];
}

int Map::isWall(int x, int y) {
	return (this->grid[x][y] > 0);
}

int Map::getWidth() {
	return this->width;
}

int Map::getHeight() {
	return this->height;
}

Map::~Map() { }
