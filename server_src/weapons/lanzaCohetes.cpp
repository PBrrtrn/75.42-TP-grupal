#include "lanzaCohetes.h"

LanzaCohetes::LanzaCohetes() : Arma() {
    const YAML::Node& c = ServerConfig::Config["LanzaCohetes"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<float>();
    this->precision = c["Precision"].as<float>();
}

bool LanzaCohetes::aimWeapon(float ort_dist, float target_dist) {
    //TODO implementar
    return false;
}

LanzaCohetes::~LanzaCohetes() {}
