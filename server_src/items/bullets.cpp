#include "bullets.h"

Bullets::Bullets(Vector pos_inicial) : Item(pos_inicial) {
    this->amount = 5;
}

bool Bullets::pickUpAction(Player& p) {
    return p.addBullets(this->amount);
}

Bullets::~Bullets(){}
