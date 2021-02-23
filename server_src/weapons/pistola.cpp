#include "pistola.h"

Pistola::Pistola() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Pistola"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<float>();
    this->precision = c["Precision"].as<float>();
}

bool Pistola::aimWeapon(float target_angle, float shooter_angle, float target_distance) {
    target_angle = target_angle * 180 / PI;
    shooter_angle = shooter_angle * 180 / PI;
    std::cout << "aim weapon pistola -- target distance: " << target_distance << "attack r: " << this->attack_range << 
        "target angle" << target_angle << "shooter angle" << shooter_angle << std::endl;
    if (target_angle < shooter_angle + this->precision/target_distance && 
        target_angle > shooter_angle - this->precision/target_distance && 
        target_distance <= this->attack_range) { return true; }
    return false;
}

Pistola::~Pistola() {}
