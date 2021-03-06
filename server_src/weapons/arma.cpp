#include "arma.h"

/*Arma::Arma() {
    this->precision = precision;
    this->cadencia = cadencia;
    this->balas = 100;
    this->indice = -1;
}*/

Arma::Arma(){
	this->nombre = "VACIA";
    this->cadencia = 0;	
    this->precision = 0;
    this->balas = 0;
    this->attack_range = 0;
    this->indice = -1;
}

int Arma::getAttackRange() {
    return this->attack_range;
}

float Arma::getCadencia() {
    return this->cadencia;
}

void Arma::printNombre() {
    std::cout << this->nombre << std::endl;
}

bool Arma::aimWeapon(float ort_dist, float target_dist) {
    return false;
}

bool Arma::is_empty() {
    return this->nombre == "VACIA";
}

bool Arma::operator==(const Arma &another) {
    return this->nombre == another.nombre;
}

int Arma::getIndex(){
	return this->indice;
}

Arma::~Arma(){}
