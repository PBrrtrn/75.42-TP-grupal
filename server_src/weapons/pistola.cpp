#include "pistola.h"

Pistola::Pistola() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Pistola"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<float>();
    this->precision = c["Precision"].as<float>();
}

bool Pistola::aimWeapon(float ort_dist, float target_dist) {
    std::cout << "Ort. dist.:" << ort_dist << std::endl;
    std::cout << "Target dist.:" << target_dist << std::endl;
    return (ort_dist < 1.5 && target_dist < this->attack_range);
    /*
    target_angle = target_angle * 180 / PI;
    shooter_angle = shooter_angle * 180 / PI;
    if (target_angle < shooter_angle + this->precision/target_distance && 
        target_angle > shooter_angle - this->precision/target_distance && 
        target_distance <= this->attack_range) { return true; }
    return false;
    */
}

Pistola::~Pistola() {}
