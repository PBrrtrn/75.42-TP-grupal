#include "arma_ametralladora.h"

ArmaAmetralladora::ArmaAmetralladora(Vector pos_inicial, bool respawns) : Item(pos_inicial,respawns) {
	this->type = TYPE_ARMA_AMETRALLADORA;
}

bool ArmaAmetralladora::pickUpAction(Player& p) {
	Ametralladora* a = new Ametralladora();
	//this->ametralladoras.push_back(a);
    if (p.addWeapon(a)){
		return true;
	} else {
		delete a;
		return false;
	}
    
    
}

ArmaAmetralladora::~ArmaAmetralladora(){
	//for(auto x: this->ametralladoras) {
	//	delete x;
	//}
}
