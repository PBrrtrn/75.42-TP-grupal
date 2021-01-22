#include "item.h"

Item::Item(Vector pos_inicial) {
	this->pos = pos_inicial;
	this->canBePicked = true;
}

bool Item::pickUpAction(Player& p) {
	return false;
}

bool Item::pickUp(Player& p){

	if(this->pickUpAction(p)) {
		this->canBePicked = false;
		return true;
	} else {
		return false;
	}
}

Vector Item::getPosition(){
	return this->pos;
}

bool Item::canBePickedUp(){
	return this->canBePicked;
}

Item::~Item() {}
