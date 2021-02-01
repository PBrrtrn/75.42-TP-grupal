#ifndef _MAP_REPOSITORY_H__
#define _MAP_REPOSITORY_H__

#include <vector>
#include <string>
#include <cstring>

#include "../server_config.h"
#include "../../common_src/Map.h"
#include "mapListItem.h"

class MapRepository {
	private:
		const YAML::Node& config;
        int map_id_counter;
        std::vector<MapListItem> maps;

	public:
		MapRepository();
        bool validMap(int mapId);
        MapListItem getMap(int mapId);
        std::string getMapLocation(int mapId);
        int getAmount();
        std::vector<MapListItem> getMapVector();
		~MapRepository();

};

#endif



