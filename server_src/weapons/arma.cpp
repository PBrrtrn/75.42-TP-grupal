#include "arma.h"

Arma::Arma(std::string config) {
    this->precision = precision;
    this->cadencia = cadencia;
    this->balas = 100;
}

Arma::Arma(){
	this->nombre = "VACIA";
    this->precision = 0;
    this->cadencia = 0;	
    this->balas = 0;
    this->attack_range = 0;
}

int Arma::getAttackRange() {
    return this->attack_range;
}

int Arma::getPrecision() {
    return this->precision;
}

bool Arma::is_empty() {
    return this->nombre == "VACIA";
}

bool Arma::operator==(const Arma &another) {
    return this->nombre == another.nombre;
}

Arma::~Arma(){}
