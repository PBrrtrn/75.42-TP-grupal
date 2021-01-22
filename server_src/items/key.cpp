#include "key.h"

Key::Key(Vector pos_inicial) : Item(pos_inicial) {}

bool Key::pickUpAction(Player& p) {
    return p.gainKey();
}

Key::~Key(){}
