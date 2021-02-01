#include "mapRepository.h"

MapRepository:: MapRepository() {
    this->map_id_counter = 0;
    const YAML::Node& config = ServerConfig::Config;
    std::string maps_location = config["Maps"]["Location"].as<std::string>();
    const YAML::Node& maps_sequence = config["MapsSequence"];

    for (YAML::const_iterator it = maps_sequence.begin(); it != maps_sequence.end(); ++it) {
        const YAML::Node& map = *it;
        MapListItem struct_map;
        struct_map.mapId = this->map_id_counter;
        //TODO CONCATENAR PATHS
        strncpy(struct_map.location, map.as<std::string>().c_str(), sizeof(struct_map.location));
        //TODO leer maxPlayers y minPlayers
        this->maps.insert({this->map_id_counter, struct_map});
        this->map_id_counter++;
    }
}

bool MapRepository::validMap(int mapId) {
    if (this->maps.find(mapId) != this->maps.end()) return true;
    return false;
}

MapListItem MapRepository::getMap(int mapId) {
    return this->maps.at(mapId);
}

MapRepository::~MapRepository(){}
