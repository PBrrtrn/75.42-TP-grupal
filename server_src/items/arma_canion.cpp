#include "arma_canion.h"

ArmaCanion::ArmaCanion(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
canion() {
	this->type = TYPE_ARMA_CANION;
	}

bool ArmaCanion::pickUpAction(Player& p) {
    return p.addWeapon(this->canion);
}

ArmaCanion::~ArmaCanion(){}
