#ifndef __SERVER_STATUS_H_
#define __SERVER_STATUS_H_

#include <unordered_map>
#include "../../common_src/GameListItem.h"
#include "../maps/mapListItem.h"
#include "../maps/mapRepository.h"
#include <vector>
////#include "thread_game.h"



class ServerStatus {
    MapRepository& mapRepo;
    public:
        /*key:id_game, value: number of players*/
        std::unordered_map<int, GameListItem>& games;
        ServerStatus(std::unordered_map<int, GameListItem>& games, MapRepository& mapRepository);
        
        char getGameListSize();
        
        std::vector<GameListItem> getGamesList();
        const std::vector<MapListItem>& getMapsList();
        
        void getGameListItem(char id,GameListItem& game);
        
        ~ServerStatus();
};

#endif
