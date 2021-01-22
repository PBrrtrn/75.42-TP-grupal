#include "treasure.h"

Treasure::Treasure(Vector pos_inicial) : Item(pos_inicial) {
    this->amount = 50; //TODO pasar a config -- VARIA EL VALOR OJO
}

bool Treasure::pickUpAction(Player& p) {
    return p.addScore(this->amount);
}

Treasure::~Treasure(){}
