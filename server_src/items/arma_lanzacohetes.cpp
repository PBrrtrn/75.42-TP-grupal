#include "arma_lanzacohetes.h"

ArmaLanzaCohetes::ArmaLanzaCohetes(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
lanza_cohetes() {
	this->type = TYPE_ARMA_LANZACOHETES;
	}

bool ArmaLanzaCohetes::pickUpAction(Player& p) {
	LanzaCohetes* lc = new LanzaCohetes();
	//this->lanza_cohetes.push_back(lc);
    if (p.addWeapon(lc)) {
		return true;
	} else {
		delete lc;
		return false;
	}
}

ArmaLanzaCohetes::~ArmaLanzaCohetes(){
	//for (auto x : this->lanza_cohetes) {
	//	delete x;
	//}
}
