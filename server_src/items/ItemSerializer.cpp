#include "ItemSerializer.h"

ItemSerializer::ItemSerializer(){}
Item ItemSerializer::deserialize(const std::string& serializedItem){
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
			return Food(Vector(positionX,positionY),true);
			break;
		case TYPE_BULLETS:
			return Bullets(Vector(positionX,positionY),true);
			break;	
		case TYPE_WATER:
			return Water(Vector(positionX,positionY),true);	
			break;
		case TYPE_TREASURE:
			return Treasure(Vector(positionX,positionY),true);	
			break;
		case TYPE_TABLE:
			return Table(Vector(positionX,positionY),false);	
			break;
		case TYPE_MEDKIT:
			return Medkit(Vector(positionX,positionY),true);	
			break;
		case TYPE_KEY:
			return Key(Vector(positionX,positionY),true);	
			break;
		case TYPE_CORPSE:
			return Corpse(Vector(positionX,positionY),false);	
			break;
		case TYPE_BLOOD:
			return Blood(Vector(positionX,positionY),true);	
			break;
		case TYPE_BARREL:
			return Barrel(Vector(positionX,positionY),false);	
			break;
		case TYPE_ARMA_AMETRALLADORA:
			return ArmaAmetralladora(Vector(positionX,positionY),true);	
			break;
		case TYPE_ARMA_CANION:
			return ArmaCanion(Vector(positionX,positionY),true);	
			break;
		case TYPE_ARMA_LANZACOHETES:
			return ArmaLanzaCohetes(Vector(positionX,positionY),true);	
			break;
		default:
			break;
	
	}
	
	return Item(Vector(0,0),false);
	
}
std::string ItemSerializer::serialize(Item& item){
	std::string serializedItem;
	
	std::string type = std::to_string(item.getType());
	
	
	
	std::string x = std::to_string(item.getPosition().getXCoordinate());
	std::string y = std::to_string(item.getPosition().getYCoordinate());
	
	return type + " " + x + " " + y;
}
ItemSerializer::~ItemSerializer(){}
