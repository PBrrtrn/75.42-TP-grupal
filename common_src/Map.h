#ifndef __MAP_H__
#define __MAP_H__

#include <vector>

class Map {
private:
	std::vector<std::vector<int>> grid; // Usar arrays
	int width;
	int height;
public:
	Map();
	Map(const char *file_location);
	~Map();
	std::vector<int>& operator[](int x);
	int getGridValue(int x, int y);
	int isWall(int x, int y);
	int getWidth();
	int getHeight();
};

#endif