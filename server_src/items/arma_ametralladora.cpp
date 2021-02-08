#include "arma_ametralladora.h"

ArmaAmetralladora::ArmaAmetralladora(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
ametralladora() {
	this->type = TYPE_ARMA_AMETRALLADORA;
	
	}

bool ArmaAmetralladora::pickUpAction(Player& p) {
    return p.addWeapon(this->ametralladora);
}

ArmaAmetralladora::~ArmaAmetralladora(){}
