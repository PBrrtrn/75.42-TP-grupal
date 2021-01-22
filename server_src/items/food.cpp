#include "food.h"

Food::Food(Vector pos_inicial) : Item(pos_inicial) {
    this->amount = 10; //TODO pasar a config
}

bool Food::pickUpAction(Player& p) {
    return p.gainHealth(this->amount);
}

Food::~Food(){}
