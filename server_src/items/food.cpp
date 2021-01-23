#include "food.h"

Food::Food(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 10; //TODO pasar a config
}

bool Food::pickUpAction(Player& p) {
    return p.gainHealth(this->amount);
}

Food::~Food(){}
