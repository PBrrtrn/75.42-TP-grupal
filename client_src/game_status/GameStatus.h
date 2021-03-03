#ifndef __GAME_STATUS_H__
#define __GAME_STATUS_H__

#include "../../common_src/Map.h"
#include "../../common_src/Vector.h"
#include "../../common_src/ClientGameStatusElements.h"
#include "../../common_src/FiringState.h"

struct GameStatusUpdate {
  Vector position;
  Vector direction;
  char selected_weapon;
  uint8_t health;
  uint8_t bullets;
  uint8_t lives;
  bool has_key;
  FiringState player_firing;
  std::vector<PlayerListItem> enemies;
  std::vector<ItemListElement> items;
};

class GameStatus {
private:
  Map map;
  PlayerStatus player_status;
  std::vector<PlayerListItem> enemies;
  std::vector<ItemListElement> items;
public:
  GameStatus();
  ~GameStatus();
  void initialize(Map new_map);
  void update(GameStatusUpdate& status_update);
  Map& getMap();
  GameStatusUpdate getUpdate();
  // bool isRunning();
};

#endif
