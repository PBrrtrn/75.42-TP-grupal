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
	
	YAML::Node mapa = YAML::LoadFile(std::string(file_location));
	
	std::cout << "opening map file:" << std::string(file_location) << std::endl;
	
	this->width = mapa["width"].as<int>();
	this->height = mapa["height"].as<int>();	
	this->grid = mapa["grid"].as<std::vector<std::vector<int>>>();
	this->minPlayers = mapa["minPlayers"].as<int>();
	this->maxPlayers = mapa["maxPlayers"].as<int>();

	
	
	/*
	//-------TODO levantar max y min players del yml----
	this->maxPlayers = 16;
	this->minPlayers = 8;
	//--------------------------------------------------
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

		/* Actualmente se guarda una fila de más en el vector si la última línea 
		  está vacía en el YML. Puede ser que necesitemos debuggear eso, pero no
		  interfiere con el correcto funcionamiento del mapa, además de que es
		  posible que cuando hagamos el parseo del YML con una biblioteca externa
		  ya venga resuelto el problema por nosotros y no sea necesario.
		  																- Pablo (27/12/2020)								 */

   /*
		std::vector<int> row;
		for (int i = 0; i < this->width; i++) {
			int value;
			stream >> value;
			row.push_back(value);
		}

		this->grid.push_back(row);
		stream.clear();
	} */
}

Map::Map(const std::string& file_location): Map(file_location.c_str()){ }

std::vector<int>& Map::operator[](int x) {
	return this->grid[x];
}

int Map::getMaxPlayers() {
	return this->maxPlayers;
}

int Map::getMinPlayers() {
	return this->minPlayers;
}

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

Map::~Map() { }
