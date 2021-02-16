#include "cuchillo.h"

Cuchillo::Cuchillo() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Cuchillo"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<float>();
    this->precision = c["Precision"].as<float>();
}

bool Cuchillo::aimWeapon(float target_angle, float shooter_angle, float target_distance) {
    if (target_distance <= this->attack_range) { return true; }
    return false;
}

Cuchillo::~Cuchillo() {}
