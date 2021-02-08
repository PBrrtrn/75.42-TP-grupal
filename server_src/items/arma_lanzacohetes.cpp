#include "arma_lanzacohetes.h"

ArmaLanzaCohetes::ArmaLanzaCohetes(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
lanza_cohetes() {
	this->type = TYPE_ARMA_LANZACOHETES;
	}

bool ArmaLanzaCohetes::pickUpAction(Player& p) {
    return p.addWeapon(this->lanza_cohetes);
}

ArmaLanzaCohetes::~ArmaLanzaCohetes(){}
