#include <iostream>
#include <sstream>
#include <fstream>

#include "Map.h"
#include "File.h"

Map::Map() { }
/* TODO: No me gusta tener que inicializar el mapa vacío y después
	volver a construirlo con file_location. Revisar eso para solo hacer
	la construción del mapa una vez (posiblemente con el objeto 
	configuración que contenga la especificación del YAML)
												- Pablo (25/12/2020)													*/

Map::Map(const char* file_location) {
	File file(file_location);

	std::stringstream stream;

	std::string line = file.getLine();
	stream << line.substr(7);
	stream >> this->width;
	stream.clear();

	line = file.getLine();
	stream << line.substr(8);
	stream >> this->height;
	stream.clear();

	while (file.hasLine()) {
		stream << file.getLine();

		std::vector<int> row;
		for (int i = 0; i < this->width; i++) {
			int value;
			stream >> value;
			row.push_back(value);
		}
		this->grid.push_back(row);
	}
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