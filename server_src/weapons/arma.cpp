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
}

bool Arma::is_empty() {
    return this->nombre == "VACIA";
}

bool Arma::operator==(const Arma &another) {
    return this->nombre == another.nombre;
}

Arma::~Arma(){}
