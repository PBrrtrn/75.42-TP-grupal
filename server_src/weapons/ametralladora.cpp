#include "ametralladora.h"

Ametralladora::Ametralladora() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Ametralladora"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<float>();
    this->precision = c["Precision"].as<float>();
}

bool Ametralladora::aimWeapon(float target_angle, float shooter_angle, float target_distance) {
    target_angle = abs(target_angle * 180 / PI);
    shooter_angle = abs(shooter_angle * 180 / PI);
    if (target_angle < shooter_angle + this->precision/target_distance && 
        target_angle > shooter_angle - this->precision/target_distance && 
        target_distance <= this->attack_range) { return true; }
    return false;
}

Ametralladora::~Ametralladora() {}
