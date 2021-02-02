#include "bullets.h"

Bullets::Bullets(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 5;
}

bool Bullets::pickUpAction(Player& p) {
    return p.addBullets(this->amount);
}

Bullets::~Bullets(){}
