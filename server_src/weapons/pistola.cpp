#include "pistola.h"

Pistola::Pistola(std::string config) : Arma(config) {
    this->nombre = "PISTOLA";
    this->attack_range = 1000000;
}

Pistola::~Pistola() {}
