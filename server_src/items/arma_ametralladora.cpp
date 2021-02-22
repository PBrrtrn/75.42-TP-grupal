#include "arma_ametralladora.h"

ArmaAmetralladora::ArmaAmetralladora(Vector pos_inicial, bool respawns) : Item(pos_inicial,respawns) {
	this->type = TYPE_ARMA_AMETRALLADORA;
}

bool ArmaAmetralladora::pickUpAction(Player& p) {
	Ametralladora* a = new Ametralladora();
	this->ametralladoras.push_back(a);
    return p.addWeapon(a);
}

ArmaAmetralladora::~ArmaAmetralladora(){
	for(auto x: this->ametralladoras) {
		delete x;
	}
}
