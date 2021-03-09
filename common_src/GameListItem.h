#ifndef __GAME_LIST_ITEM_H_
#define __GAME_LIST_ITEM_H_

#include <stdint.h>

struct GameListItem {
	char gameId;
	uint8_t players;
	uint8_t maxPlayers;
	char mapId;
};

#endif
