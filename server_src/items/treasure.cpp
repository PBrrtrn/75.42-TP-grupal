#include "treasure.h"

Treasure::Treasure(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    const YAML::Node& c = ServerConfig::Config["Treasure"];
    this->amount = c["Points"].as<int>();
    this->type = TYPE_TREASURE;
}

bool Treasure::pickUpAction(Player& p) {
    return p.addScore(this->amount);
}

Treasure::~Treasure(){}
