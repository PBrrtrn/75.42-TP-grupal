#include "item.h"

Item::Item(Vector pos_inicial) {
	this->pos = pos_inicial;
}

bool Item::pickUp(Player& p){
	
	//ejecutar cambio de estado si el pickup fue exitoso (this->canBePickedUp = false);
	
	//si el item cura
	//return p.gainHealth(this->amount);

	//si el item son balas
	//return p.addBullets(this->amount);
	
	//si el item es un arma
	//return p.addWeapon(this->weapon);
	
	//si el item es un tesoro
	//return p.addScore(this->amount);
	
	//si el item es una llave
	//return p.gainKey();	
	
	return true;
	
}

Vector Item::getPosition(){
	return this->pos;
}

bool Item::canBePickedUp(){
	return this->canBePicked;
}

Item::~Item() {}
