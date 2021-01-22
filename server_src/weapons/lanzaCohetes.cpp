#include "lanzaCohetes.h"

LanzaCohetes::LanzaCohetes(std::string config) : Arma(config) {
    this->nombre = "LANZA_COHETES";
    this->attack_range = 1000000;
}

LanzaCohetes::~LanzaCohetes() {}
