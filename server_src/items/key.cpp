#include "key.h"

Key::Key(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
	this->type = TYPE_KEY;
	
	}

bool Key::pickUpAction(Player& p) {
    return p.gainKey();
}

Key::~Key(){}
