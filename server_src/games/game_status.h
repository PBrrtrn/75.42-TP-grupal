#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include <iostream>
#include <string>
#include <vector>
#include "../../common_src/Vector.h"
#include "MapServer.h"
#include <unordered_map>
#include "player.h"
#include "../items/item.h"
#include "../items/arma_ametralladora.h"
#include "door.h"
#include "statistics.h"
#include "../../common_src/FiringState.h"
#include "../../common_src/respawn_event.h"

class GameStatus {
  
private:
  Vector position;
  Statistics statistics;
  std::unordered_map<int, Vector> playersPositions;
  std::unordered_map<int, Vector> playersDirections;
  std::unordered_map<int, Player> players;
  std::unordered_map<int, Door> doors;
  std::vector<Item*> items;
  Vector angle;
  MapServer map;
  std::string mapLocation;
  std::string entireMap;
  float itemPickUpRange;

  /*clave: id del cliente, valor: timed event para disparar*/
  std::unordered_map<int,RespawnEvent*> respawn_events;

  void loadDoors();
  
public:
  
  GameStatus(std::string mapLocation);
  Vector getPosition();
  //float getAngle();
  void addPlayer(int playerID, Vector &position, Vector &direction);
  Vector getPosition(int playerID);
  Vector getDirection(int playerID);
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
  int getMinPlayers();
	std::vector<Item*>& getMapItems();
  std::vector<Item*>& getGsItems();
  float getShootTimeout(int playerID);
  std::vector<SpawnPoint> getSpawnPoints();
  
  std::string getEntireMap();
  Map& getMap();
  
  //void updatePlayerPositions();
  
  std::unordered_map<int,MovementState> getPlayerMovementStates();
  std::unordered_map<int,MovementState> getPlayerRotationStates();
  
  bool changeMovementState(int clientId,MovementState state);
  bool changeShootingState(int playerId, ShootingState state);
  bool changeRotationState(int clientId,MovementState state);
  bool changeFiringState(int clientId, FiringState state);
    
  Statistics& showStatistics();

  void resetPlayerStatusEvents();
  void fillRespawnEvents();
  void respawnPlayer(int playerID);
  void updateRespawnEvents(double delta);

  bool isPlayer(Vector& position);
  
  int* getMapGrid();
  int getMapWidth();
  int getMapHeight();
    
  friend class Action;
  friend class Shoot;
  friend class ChangeWeaponCuchillo;
  friend class ChangeWeaponPistola;
  friend class ChangeWeaponAmetralladora;
  friend class ChangeWeaponCanion;
  friend class ChangeWeaponLanzaCohetes;
  friend class UseDoor;
  friend class MoveBackward;
  friend class MoveForward;
  friend class MoveLeft;
  friend class MoveRight;
  friend class Shoot;
    
  friend class ClientGameStatus;
    
  ~GameStatus();
};

#endif //GAMESTATUS_H
