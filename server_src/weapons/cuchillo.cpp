#include "cuchillo.h"

Cuchillo::Cuchillo() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Cuchillo"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<double>();
    this->precision = c["Precision"].as<float>();
}

bool Cuchillo::aimWeapon(float ort_dist, float target_dist) {
    if (target_dist <= this->attack_range && ort_dist <= this->precision) { return true; }
    return false;
}

Cuchillo::~Cuchillo() {}
