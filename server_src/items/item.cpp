#include "item.h"

Item::Item(Vector pos_inicial,bool respawns) {
	this->pos = pos_inicial;
	this->canBePicked = true;
	this->respawns = respawns;
	this->timeToRespawn = 600; //600 frames, 10 segundos
	this->isDecoration = false;
	this->has_volume = false;
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

bool Item::isVisible(){
	
	if (this->canBePicked && !this->isDecoration) {
		return true;
	}
	else if (!this->canBePicked && !this->isDecoration) {
		return false;
	}
	else if (!this->canBePicked && this->isDecoration) {
		return true;
	} 
	
	return true;
	//si se puede levantar y no es decoracion ->es visible -- es un item que se puede levantar
	//si no se puede levantar y no es decoracion -> es invisible -- es un item que todavia no respawneo
	//si no se puede levantar y es decoracion -> es visible --es un barrel / corpse
}

bool Item::hasVolume(){
	return has_volume;
}

ItemType Item::getType(){
	return this->type;
}


Item::~Item() {}
