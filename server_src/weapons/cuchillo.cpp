#include "cuchillo.h"

Cuchillo::Cuchillo() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Cuchillo"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
}

Cuchillo::~Cuchillo() {}
