#include "lanzaCohetes.h"

LanzaCohetes::LanzaCohetes() : Arma() {
    const YAML::Node& c = ServerConfig::Config["LanzaCohetes"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<int>();
    this->precision = c["Precision"].as<int>();
}

bool LanzaCohetes::aimWeapon(float target_angle, float shooter_angle, float target_distance) {
    //TODO implementar
    return false;
}

LanzaCohetes::~LanzaCohetes() {}
