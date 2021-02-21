#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>

class Map {
private:
	std::vector<std::vector<int>> grid; 
	int width;
	int height;
	
public:
	Map();
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
};

#endif
