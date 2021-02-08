#include "DoorSerializer.h"

DoorSerializer::DoorSerializer(){}
Door DoorSerializer::deserialize(const std::string& serializedDoor){
	std::stringstream ss(serializedDoor);
	std::string word;
	float gridLocationX;
	float gridLocationY;
	bool isLocked;
	
	ss >> word;
	isLocked = (word == "1");
	ss >> gridLocationX;
	ss >> gridLocationY;
	
	return Door(isLocked,gridLocationX,gridLocationY);
	
}
std::string DoorSerializer::serialize(Door& door){
	std::string locked = std::to_string(door.isLocked());
	
	std::string x = std::to_string(door.getLocation().getXCoordinate());
	std::string y = std::to_string(door.getLocation().getYCoordinate());
	
	return locked + " " + x + " " + y;
}
DoorSerializer::~DoorSerializer(){}
