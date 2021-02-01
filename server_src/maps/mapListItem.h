#ifndef __MAP_LIST_ITEM_H_
#define __MAP_LIST_ITEM_H_

struct MapListItem {
    int mapId;
    char location[30];
    int maxPlayers;
    int minPlayers;
};

#endif
