#include "SpawnPointSerializer.h"

SpawnPointSerializer::SpawnPointSerializer(){}
SpawnPoint SpawnPointSerializer::deserialize(const std::string& serializedSP){
	std::stringstream ss(serializedSP);
	float positionX;
	float positionY;
	float directionX;
	float directionY;
	
	ss >> positionX;
	ss >> positionY;
	ss >> directionX;
	ss >> directionY;
	
	return SpawnPoint(Vector(positionX,positionY),Vector(directionX,directionY));
	
}
std::string SpawnPointSerializer::serialize(SpawnPoint& sp){

	std::string positionX = std::to_string(sp.getPosition().getXCoordinate());
	std::string positionY = std::to_string(sp.getPosition().getYCoordinate());
	std::string directionX = std::to_string(sp.getDirection().getXCoordinate());
	std::string directionY = std::to_string(sp.getDirection().getYCoordinate());
	
	return positionX + " " + positionY + " " + directionX + " " + directionY;
}
SpawnPointSerializer::~SpawnPointSerializer(){}
