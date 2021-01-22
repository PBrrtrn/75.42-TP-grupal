#include "cuchillo.h"

Cuchillo::Cuchillo(std::string config) : Arma(config) {
    this->nombre = "CUCHILLO";
    this->attack_range = 1;
}

Cuchillo::~Cuchillo() {}
