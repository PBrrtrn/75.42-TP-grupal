#include "arma_canion.h"

ArmaCanion::ArmaCanion(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
	this->type = TYPE_ARMA_CANION;
}

bool ArmaCanion::pickUpAction(Player& p) {
	CanionDeCadena* c = new CanionDeCadena();
   	if (p.addWeapon(c)) {
		return true;
	} else {
		delete c;
		return false;
	}
}

ArmaCanion::~ArmaCanion(){}
