#include "pistola.h"

Pistola::Pistola() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Pistola"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<int>();
    this->precision = c["Precision"].as<int>();
}

bool Pistola::aimWeapon(float target_angle, float shooter_angle, float target_distance) {
    if (target_angle < shooter_angle + this->precision/target_distance && 
        target_angle > shooter_angle - this->precision/target_distance && 
        target_distance <= this->attack_range) { return true; }
    return false;
}

Pistola::~Pistola() {}
