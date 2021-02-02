#include "treasure.h"

Treasure::Treasure(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 50; //TODO pasar a config -- VARIA EL VALOR OJO
}

bool Treasure::pickUpAction(Player& p) {
    return p.addScore(this->amount);
}

Treasure::~Treasure(){}
