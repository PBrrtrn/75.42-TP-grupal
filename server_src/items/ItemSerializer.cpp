#include "ItemSerializer.h"

ItemSerializer::ItemSerializer(){}

Item* ItemSerializer::deserialize(const std::string& serializedItem){
	std::stringstream ss(serializedItem);
	std::string word;
	ItemType type;
	float positionX;
	float positionY;
	
	ss >> word;
	type = (ItemType)std::stoi(word);
	ss >> positionX;
	ss >> positionY;
	
	switch (type) {
		case TYPE_FOOD:
			return new Food(Vector(positionX,positionY),true);
			break;
		case TYPE_BULLETS:
			return new Bullets(Vector(positionX,positionY),true);
			break;	
		case TYPE_WATER:
			return new Water(Vector(positionX,positionY),true);	
			break;
		case TYPE_TREASURE:
			return new Treasure(Vector(positionX,positionY),true);	
			break;
		case TYPE_TABLE:
			return new Table(Vector(positionX,positionY),false);	
			break;
		case TYPE_MEDKIT:
			return new Medkit(Vector(positionX,positionY),true);	
			break;
		case TYPE_KEY:
			return new Key(Vector(positionX,positionY),true);	
			break;
		case TYPE_CORPSE:
			return new Corpse(Vector(positionX,positionY),false);	
			break;
		case TYPE_BLOOD:
			return new Blood(Vector(positionX,positionY),true);	
			break;
		case TYPE_BARREL:
			return new Barrel(Vector(positionX,positionY),false);	
			break;
		case TYPE_ARMA_AMETRALLADORA:
			return new ArmaAmetralladora(Vector(positionX,positionY),true);	
			break;
		case TYPE_ARMA_CANION:
			return new ArmaCanion(Vector(positionX,positionY),true);	
			break;
		case TYPE_ARMA_LANZACOHETES:
			return new ArmaLanzaCohetes(Vector(positionX,positionY),true);	
			break;
		default:
			break;
	
	}
	
	return new Item(Vector(0,0),false);
	
}
std::string ItemSerializer::serialize(Item* item){
	std::string serializedItem;
	
	std::string type = std::to_string(item->getType());

	std::string x = std::to_string(item->getPosition().getXCoordinate());
	std::string y = std::to_string(item->getPosition().getYCoordinate());
	
	return type + " " + x + " " + y;
}
ItemSerializer::~ItemSerializer(){}
