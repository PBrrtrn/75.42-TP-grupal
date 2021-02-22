#include "medkit.h"

Medkit::Medkit(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    const YAML::Node& c = ServerConfig::Config["Medkit"];
    this->amount = c["Points"].as<int>();
    this->type = TYPE_MEDKIT;
}

bool Medkit::pickUpAction(Player& p) {
    return p.gainHealth(this->amount);
}

Medkit::~Medkit(){}
