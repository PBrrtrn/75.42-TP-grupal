#include "lanzaCohetes.h"

LanzaCohetes::LanzaCohetes() : Arma() {
    const YAML::Node& c = ServerConfig::Config["LanzaCohetes"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->timeout = c["Timeout"].as<int>();
}

LanzaCohetes::~LanzaCohetes() {}
