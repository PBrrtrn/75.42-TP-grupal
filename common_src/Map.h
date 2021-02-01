#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <string>

class Map {
private:
	std::vector<std::vector<int>> grid; // Usar arrays
	int width;
	int height;
	int minPlayers;
	int maxPlayers;
public:
	Map();
	Map(const char *file_location);
	Map(const std::string& file_location);
	~Map();
	std::vector<int>& operator[](int x);
	int getGridValue(int x, int y);
	int isWall(int x, int y);
	int getWidth();
	int getHeight();
	int getMaxPlayers();
	int getMinPlayers();
};

#endif
