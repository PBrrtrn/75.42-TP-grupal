#ifndef __MAP_H__
#define __MAP_H__

#include "MapData.h"

// uso:
//	MapData md("map-data.yml");
//	Map map(md);

class Map{
private:
	std::vector<GridRow> grid;
	int width;
	int height;
public:
	Map() { }
	Map(MapData m) : grid(m.grid),width(m.width),height(m.height){ }
	int getValue(int x_position,int y_position){
		return grid[x_position][y_position];
	}
	int isWall(int x_position,int y_position){
		return grid[x_position][y_position] > 0;
	}	
	
	int getWidth() { 
		return this->width;
	}
	int getHeight() { 
		return this->height;
	}
	
	
};

#endif