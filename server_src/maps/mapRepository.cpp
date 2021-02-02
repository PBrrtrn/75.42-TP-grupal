#include "mapRepository.h"

MapRepository:: MapRepository(): config(ServerConfig::Config) {
    this->map_id_counter = 0;
    std::string maps_location = this->config["Maps"]["Location"].as<std::string>();
    const YAML::Node& maps_sequence = this->config["MapsSequence"];

    for (YAML::const_iterator it = maps_sequence.begin(); it != maps_sequence.end(); ++it) {
        const YAML::Node& map = *it;
        MapListItem struct_map;
        struct_map.mapId = this->map_id_counter;
        strncpy(struct_map.name, map.as<std::string>().c_str(), sizeof(struct_map.name));
        //TODO leer maxPlayers y minPlayers
        struct_map.maxPlayers = 16;
        struct_map.minPlayers = 8;
        this->maps.push_back(struct_map);
        this->map_id_counter++;
    }
}

int MapRepository::getAmount() {
    return this->maps.size();
}

bool MapRepository::validMap(int mapId) {
    if (mapId < this->maps.size()) return true;
    return false;
}

MapListItem MapRepository::getMap(int mapId) {
    return this->maps.at(mapId);
}

std::string MapRepository::getMapLocation(int mapId) {
	std::string maps_location = this->config["Maps"]["Location"].as<std::string>();
    return maps_location + std::string(this->maps.at(mapId).name);
}

const std::vector<MapListItem>& MapRepository:: getMapVector() {
    return this->maps;
}

MapRepository::~MapRepository(){}
