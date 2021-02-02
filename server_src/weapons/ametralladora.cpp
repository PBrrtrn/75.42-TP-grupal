#include "ametralladora.h"

Ametralladora::Ametralladora() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Ametralladora"];

    this->precision = c["Precision"].as<int>();
    this->cadencia = c["Cadencia"].as<double>();
    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
}

Ametralladora::~Ametralladora() {}
