#ifndef __CLIENT_GAME_STATUS_ELEMENTS_H
#define __CLIENT_GAME_STATUS_ELEMENTS_H

#include "Vector.h"
#include "ItemType.h"
#include "FiringState.h"

#define TOP_STATISTICS 10

//estatus del player asociado a este GameStatus
struct PlayerStatus{
	Vector position;
	Vector direction;
	char selectedWeapon;
	uint8_t health;
	uint8_t bullets;
	uint8_t lives;
	bool hasKey;
	FiringState firing_state;
};

//listado de puertas
struct DoorListItem{
	int doorId;
	Vector gridPosition;
	bool isOpen;
};

//listado de Jugadores que no son el player asociado a este GameStatus
struct PlayerListItem {
	char clientId;
	Vector position;
	Vector direction;
	uint8_t selectedWeapon;
	bool isAlive;
};

//listado de items asociados a este 
struct ItemListElement {
	ItemType type;
	Vector pos;
	bool isVisible;
};

struct ClientKills {
	char clientId;
	int kills;
};

struct ClientPoints {
	char clientId;
	int puntaje;
};

struct ClientShootedBullets {
	char clientId;
	int bullets_shooted;
};

struct GameStatistics {
	ClientKills kills[TOP_STATISTICS];
	ClientPoints points[TOP_STATISTICS];
	ClientShootedBullets bullets[TOP_STATISTICS];
};

#endif
