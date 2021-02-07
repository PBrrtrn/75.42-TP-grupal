#include "Map.h"

Map::Map() { }

Map::Map(char* file_content){
	
	//YAML::Node mapa = YAML::LoadFile(file_content);
	
	//this->width = mapa["width"].as<int>();
	//this->height = mapa["height"].as<int>();	
	//this->grid = mapa["grid"].as<std::vector<std::vector<int>>>();	
}

Map::Map(const char* file_location) {
	YAML::Node mapa = YAML::LoadFile(std::string(file_location));
	this->width = mapa["width"].as<int>();
	this->height = mapa["height"].as<int>();	
	this->grid = mapa["grid"].as<std::vector<std::vector<int>>>();	
}

Map::Map(const std::string& file_location): Map(file_location.c_str()){ }

std::vector<int>& Map::operator[](int x) {
	return this->grid[x];
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
