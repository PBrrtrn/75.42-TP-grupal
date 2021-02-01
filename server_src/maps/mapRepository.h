#ifndef _MAP_REPOSITORY_H__
#define _MAP_REPOSITORY_H__

#include <unordered_map>
#include <string>
#include <cstring>

#include "../server_config.h"
#include "../../common_src/Map.h"
#include "mapListItem.h"

class MapRepository {
	private:
        int map_id_counter;
        /*key: map id, value: clase Map*/
        std::unordered_map<int, MapListItem> maps;

	public:
		MapRepository();
        bool validMap(int mapId);
        MapListItem getMap(int mapId);
		~MapRepository();

};

#endif



