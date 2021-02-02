#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <iostream>
#include <string>
#include <vector>
#include "../../common_src/Vector.h"
#include "../../common_src/Map.h"
#include <unordered_map>
#include "player.h"
#include "../items/item.h"
#include "../items/arma_ametralladora.h"
#include <vector>
#include "door.h"
#include "statistics.h"

class GameStatus {
	
private:
	Vector position;
	Statistics statistics;
	std::unordered_map<int, Vector> playersPositions;
	std::unordered_map<int, Vector> playersDirections;
	std::unordered_map<int,Player> players;
	std::unordered_map<int,Door> doors;
	std::vector<Item> items;
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
    void checkPlayerPickups();
    void checkPlayerBullets();
    void respawnItems();
	void addEnemyDead(int playerID);
	void addBulletShooted(int playerID);
	void addPointTreasure(int playerID);
	int getAlivePlayers();
	int getMaxPlayers();
    
	Statistics showStatistics();
    
    friend class Action;
	friend class Shoot;
	friend class ChangeWeaponCuchillo;
	friend class ChangeWeaponPistola;
	friend class ChangeWeaponAmetralladora;
	friend class ChangeWeaponCanion;
	friend class ChangeWeaponLanzaCohetes;
	friend class UseDoor;
    
	~GameStatus();
};

#endif //GAMESTATUS_H
