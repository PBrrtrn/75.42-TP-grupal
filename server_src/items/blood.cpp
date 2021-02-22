#include "blood.h"

Blood::Blood(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    const YAML::Node& c = ServerConfig::Config["Blood"];
    this->amount = c["Points"].as<int>();
    this->type = TYPE_BLOOD;
}

bool Blood::pickUpAction(Player& p) {
    if (p.getHealth() < 11) {
        return p.gainHealth(this->amount);
    }
    return false;
}

Blood::~Blood(){}
