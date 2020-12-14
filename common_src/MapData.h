#ifndef __MAPDATA_H__
#define __MAPDATA_H__

#include <vector>
#include <sstream>
#include <fstream>

class GridRow : public std::vector<int> {};

// uso:
//	MapData md("map-data.yml");
//	Map map(md);

class MapData{
public:
	std::vector<GridRow> grid;
	int width;
	int height;
	
	MapData(const std::string& file_location){
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
				GridRow row;
				
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
};

#endif