#include "canionDeCadena.h"

CanionDeCadena::CanionDeCadena() : Arma() {
    const YAML::Node& c = ServerConfig::Config["CanionDeCadena"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<double>();
    this->precision = c["Precision"].as<float>();
}

bool CanionDeCadena::aimWeapon(float ort_dist, float target_dist) {
    return (ort_dist < this->precision && target_dist < this->attack_range);
}

CanionDeCadena::~CanionDeCadena() {}
