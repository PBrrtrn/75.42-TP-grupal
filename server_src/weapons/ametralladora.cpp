#include "ametralladora.h"

Ametralladora::Ametralladora() : Arma() {
    this->precision = 10;
    this->cadencia = 0.1;
    this->nombre = "AMETRALLADORA";
    this->attack_range = 1000000;
    this->indice = 2;
}

Ametralladora::~Ametralladora() {}
