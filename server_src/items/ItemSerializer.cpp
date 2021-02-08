#include "ItemSerializer.h"


ItemSerializer::ItemSerializer(){}
Item ItemSerializer::deserialize(const std::string& serializedItem){
	std::stringstream ss(serializedItem);
	std::string word;
	ItemType type;
	int positionX;
	int positionY;
	
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
