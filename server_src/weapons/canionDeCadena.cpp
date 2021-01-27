#include "canionDeCadena.h"

CanionDeCadena::CanionDeCadena() : Arma() {
    const YAML::Node& c = ServerConfig::Config["CanionDeCadena"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
}

CanionDeCadena::~CanionDeCadena() {}
