#include "item.h"

Item::Item(Vector pos_inicial,bool respawns) {
	this->pos = pos_inicial;
	this->canBePicked = true;
	this->respawns = respawns;
	this->timeToRespawn = 600; //600 frames, 10 segundos
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

bool Item::tick(){
	if (!this->canBePicked && this->respawns){
		if (this->timeToRespawn <= 0){
			this->canBePicked = true;
			this->timeToRespawn = 600;
		} else {
			this->timeToRespawn--;
		}
	}
	return this->canBePicked;
}

int Item::getTimeToRespawn(){
	return this->timeToRespawn;
}

Item::~Item() {}
