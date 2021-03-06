#include "ametralladora.h"

Ametralladora::Ametralladora() : Arma() {
    const YAML::Node& c = ServerConfig::Config["Ametralladora"];

    this->nombre = c["Nombre"].as<std::string>();
    this->attack_range = c["AttackRange"].as<int>();
    this->indice = c["Idx"].as<int>();
    this->cadencia = c["Cadencia"].as<double>();
    this->precision = c["Precision"].as<float>();
}

bool Ametralladora::aimWeapon(float ort_dist, float target_dist) {
    std::cout << "Ort. dist.:" << ort_dist << std::endl;
    std::cout << "Target dist.:" << target_dist << std::endl;
    return (ort_dist < this->precision && target_dist < this->attack_range);
}

Ametralladora::~Ametralladora() {}
