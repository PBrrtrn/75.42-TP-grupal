#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>
////#include "../server_src/items/item.h"
////#include "../server_src/games/door.h"
////#include "Vector.h"
#include "File.h"
////#include "../server_src/items/food.h"

class Map {
private:
	std::vector<std::vector<int>> grid; 
	int width;
	int height;
	
public:
	Map();
	Map(int width,int height);
	Map(int width,int height,int* mapData);
	int* getMapGridCopy();
	Map(char* file_content);
	Map(const char *file_location);
	Map(const std::string& file_location);
	~Map();
	std::vector<int>& operator[](int x);
	int getGridValue(int x, int y);
	void setGridValue(int x, int y,int newValue);
	int isWall(int x, int y);
	int getWidth();
	int getHeight();
	std::string getSerializedMap();
};

#endif
