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
#include "./SpawnPoint.h"
#include "../games/DoorSerializer.h"
#include "../games/SpawnPointSerializer.h"
#include "../items/ItemSerializer.h"

class MapServer {
private:
	Map map;
	int minPlayers;
	int maxPlayers;
	
	std::vector<std::string> items_yml;
	std::vector<Item*> items;
	std::vector<std::string> doors_yml;
	std::vector<Door> doors;
	std::vector<SpawnPoint> respawnPoints;
	std::vector<std::string> spawnpoints_yml;

	void loadItems();
	void loadDoors();
	void loadSpawnPoints();
	ItemSerializer item_serializer;
	DoorSerializer door_serializer;
	SpawnPointSerializer spawnpoints_serializer;

public:
	MapServer(const std::string& file_location);
	MapServer(int width,int height,int minPlayers,int maxPlayers);
	MapServer(MapServer&& from);
	std::string getSerializedMap();
	void setGridValue(int x, int y,int newValue);
	~MapServer();
	std::vector<int>& operator[](int x);
	int getGridValue(int x, int y);
	int isWall(int x, int y);
	bool isObstacle(Vector position);
	int getWidth();
	int getHeight();
	int getMaxPlayers();
	int getMinPlayers();
	Map& getMap();
	void insertItem(Item* item);
	void insertSpawnPoint(SpawnPoint s);
	
	std::vector<Item*>& getItems();
	std::vector<Door>& getDoors();
	std::vector<SpawnPoint>& getRespawnPoints();
	
	int* getMapGridCopy();
	
};

#endif
