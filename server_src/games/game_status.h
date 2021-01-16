#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <iostream>
#include <string>
#include <vector>
#include "vector.h"
#include "../../common_src/Map.h"
#include <unordered_map>

class GameStatus{
	
	Vector position;
	std::unordered_map<int, Vector> playersPositions;
	std::unordered_map<int, Vector> playersDirections;
	Vector angle;
	Map map;
	
public:
	
	GameStatus(std::string mapLocation);
	Vector getPosition();
	float getAngle();
	void addPlayer(int playerID, Vector &position, Vector &direction);
	Vector getPosition(int playerID);
	float getAngle(int playerID);
	void setPosition(int playerID, Vector &position);
    void setPosition(int playerID, float x, float y);
    void setAngle(int playerID, float angle);
    
    friend class Action;
    
	~GameStatus();
};

#endif //GAMESTATUS_H
