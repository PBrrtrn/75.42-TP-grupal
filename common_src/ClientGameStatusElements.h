#ifndef __CLIENT_GAME_STATUS_ELEMENTS_H
#define __CLIENT_GAME_STATUS_ELEMENTS_H
#include "Vector.h"
#include "ItemType.h"
#define TOP_STATISTICS 10

//estatus del player asociado a este GameStatus
struct PlayerStatus{
	char clientId;
	Vector position;
	Vector direction;
	char selectedWeapon;
	char health;
	char bullets;
	char lives;
	bool hasKey;
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
	char selectedWeapon;
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
