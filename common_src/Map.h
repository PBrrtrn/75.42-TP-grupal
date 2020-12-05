#ifndef __MAP_H__
#define __MAP_H__

#include "MapData.h"

// uso:
//	MapData md("map-data.yml");
//	Map map(md);

class Map{
private:
	std::vector<GridRow> grid;
public:
	Map(MapData m) : grid(m.grid){ }
	int getValue(int x_position,int y_position){
		return grid[x_position][y_position];
	}
};

#endif
