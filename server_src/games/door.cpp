#include "door.h"

Door::Door(bool is_locked,int xGridLocation,int yGridLocation){
	this->locked = is_locked;
	this->open = false;
	this->time_to_close = 0;
	this->location = Vector(xGridLocation*64,yGridLocation*64);
}

bool Door::isLocked(){
	return this->locked;
}
bool Door::isOpen(){
	return this->open;
}

int Door::getTimeToClose(){
	return this->time_to_close;
}

void Door::openDoor(){
	this->open = true;
	this->time_to_close = 10;
}
void Door::unlockDoor(){
	this->locked = false;
}

Vector Door::getLocation(){
	return this->location;
}

Door::~Door() {}
