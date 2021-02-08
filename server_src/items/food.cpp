#include "food.h"

Food::Food(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 10; //TODO pasar a config
    this->type = TYPE_FOOD;
}

bool Food::pickUpAction(Player& p) {
    return p.gainHealth(this->amount);
}

Food::~Food(){}
