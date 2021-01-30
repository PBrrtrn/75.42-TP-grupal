#ifndef __SERVER_STATUS_H_
#define __SERVER_STATUS_H_

#include <unordered_map>
#include "../../common_src/GameListItem.h"
#include <vector>
////#include "thread_game.h"



class ServerStatus {
    public:
        /*key:id_game, value: number of players*/
        std::unordered_map<int, GameListItem>& games;
        //std::unordered_map<int, Map*>& maps;
        //ServerStatus(std::unordered_map<int, ThreadGame*>& games);
        ServerStatus(std::unordered_map<int, GameListItem>& games);
        
        char getGameListSize();
        
        std::vector<GameListItem> getGamesList();
        
        void getGameListItem(char id,GameListItem& game);
        
        ~ServerStatus();
};

#endif
