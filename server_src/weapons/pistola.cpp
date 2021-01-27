#include "pistola.h"

Pistola::Pistola() : Arma() {
    this->nombre = "PISTOLA";
    this->attack_range = 1000000;
    this->indice = 1;
}

Pistola::~Pistola() {}
