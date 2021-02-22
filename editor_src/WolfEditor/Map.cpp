#include "Map.h"

Map::Map() { }

Map::Map(int width,int height){
    this->width = width;
    this->height = height;

    for (int row = 0; row < height; row++){
        this->grid.push_back(std::vector<int>(width, 0));
    }

}

Map::Map(const char* file_location) {
	YAML::Node map = YAML::LoadFile(std::string(file_location));
	this->width = map["width"].as<int>();
	this->height = map["height"].as<int>();	
	this->grid = map["grid"].as<std::vector<std::vector<int>>>();	
}

Map::Map(const std::string& file_location): Map(file_location.c_str()){ }

std::vector<int>& Map::operator[](int x) {
	return this->grid[x];
}

int Map::getGridValue(int x, int y) {
	return this->grid[y][x];
}

void Map::setGridValue(int x, int y,int newValue) {
    this->grid[y][x] = newValue;
}

int Map::isWall(int x, int y) {
	return (this->grid[y][x] > 0);
}

int Map::getWidth() {
	return this->width;
}

int Map::getHeight() {
	return this->height;
}

std::string Map::getSerializedMap() {
    YAML::Emitter outMap;
    outMap << YAML::BeginMap;
        outMap << YAML::Key << "width";
        outMap << YAML::Value << this->width ;
        outMap << YAML::Key << "height";
        outMap << YAML::Value << this->height ;
        outMap << YAML::Key << "grid";
        outMap << YAML::Value << YAML::Flow << this->grid;
    outMap << YAML::EndMap;

    return std::string(outMap.c_str());
}

Map::~Map() { }
