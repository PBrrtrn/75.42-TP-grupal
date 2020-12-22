#ifndef __GAME_STATUS_H__
#define __GAME_STATUS_H__

#include "../common_src/Map.h"
#include "../common_src/Vector.h"

struct GameStatusUpdate {
	Vector player_position;
	int player_health;
	int player_weapon;
	int player_ammo;
	GameStatusUpdate();
	~GameStatusUpdate();
};

struct PlayerStatus {
	Vector position;
	int health;
	int current_weapon;
	int current_weapon_ammo;
	PlayerStatus();
	~PlayerStatus();
};

class GameStatus {
private:
	Map map;
	PlayerStatus player_status;
public:
	GameStatus();
	~GameStatus();
	void initialize(Map& new_map, GameStatusUpdate& initial_state);
	void update(GameStatusUpdate& status_update);
};

#endif
