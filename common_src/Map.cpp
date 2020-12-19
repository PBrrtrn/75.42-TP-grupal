#include <sstream>
#include <fstream>

#include "Map.h"

Map::Map(const char* file_location) {
	this->width = 0;
	this->height = 0;

	std::ifstream input_file;
	input_file.open(file_location);
	int i = 0;
	while (!input_file.eof()){
		std::string current_line;
		std::getline(input_file,current_line);
		std::stringstream s;
		std::string piece;
		s << current_line;

		if (this->width == 0 || this->height == 0){
			while (s >> piece){
				if (piece == "width:"){
					s >> this->width;
				}
				if (piece == "height:"){
					s >> this->height;
				}					
			}
		} else {
			std::vector<int> row;
			
			for (int j = 0;j < this->width;j++){
				int value;
				s >> value;
				row.push_back(value);
			}
			this->grid.push_back(row);
			i++;
		}
	}

	input_file.close();
}

Map::~Map() { }

int Map::getGridValue(int x, int y) {
	return this->grid[x][y];
}

int Map::isWall(int x, int y) {
	return (this->grid[x][y] > 0);
}

int Map::getWidth() {
	return this->width;
}

int Map::getHeight() {
	return this->height;
}