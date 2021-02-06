#ifndef __MAP_SERVER_H__
#define __MAP_SERVER_H__

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "../../common_src/Map.h"
#include "../items/item.h"
#include "../games/door.h"
#include "../../common_src/Vector.h"
#include "../items/food.h"


class MapServer {
private:
	Map map;
	int minPlayers;
	int maxPlayers;
	
	std::vector<Item> items;
	std::vector<Door> doors;
	std::vector<Vector> respawnPoints;
public:
	MapServer(const std::string& file_location);
	~MapServer();
	std::vector<int>& operator[](int x);
	int getGridValue(int x, int y);
	int isWall(int x, int y);
	int getWidth();
	int getHeight();
	int getMaxPlayers();
	int getMinPlayers();
	
	std::vector<Item> getItems();
	std::vector<Door> getDoor();
	std::vector<Vector> getRespawnPoints();
	
};

#endif
