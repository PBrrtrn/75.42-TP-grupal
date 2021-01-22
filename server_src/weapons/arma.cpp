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

Arma::~Arma(){}
