#include "food.h"

Food::Food(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    const YAML::Node& c = ServerConfig::Config["Food"];
    this->amount = c["Points"].as<int>();
    this->type = TYPE_FOOD;
}

bool Food::pickUpAction(Player& p) {
    std::cout << "pickupeando FOOD" << std::endl;
    return p.gainHealth(this->amount);
}

Food::~Food(){}
