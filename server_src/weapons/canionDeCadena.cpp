#include "canionDeCadena.h"

CanionDeCadena::CanionDeCadena(std::string config) : Arma(config) {
    this->nombre = "CANION_DE_CADENA";
    this->attack_range = 1000000;
    this->indice = 3;
}

CanionDeCadena::~CanionDeCadena() {}
