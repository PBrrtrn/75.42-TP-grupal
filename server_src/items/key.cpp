#include "key.h"

Key::Key(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {}

bool Key::pickUpAction(Player& p) {
    return p.gainKey();
}

Key::~Key(){}
