#include "arma.h"

Arma::Arma(std::string config) {
    this->precision = precision;
    this->cadencia = cadencia;
}

Arma::Arma(){
	this->nombre = "VACIA";
    this->precision = 0;
    this->cadencia = 0;	
	}

Arma::~Arma(){}
