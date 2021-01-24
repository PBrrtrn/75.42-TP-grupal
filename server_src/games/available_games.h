#ifndef AVAILABLE_GAMES_H
#define AVAILABLE_GAMES_H

#include <unordered_map>

class AvailableGames {
    public:
        /*key:id_game, value: number of players*/
        std::unordered_map<int,int> games;
        AvailableGames();
        //std::unordered_map<int,int> getAvailableGames(); TODO PASAR A BINARIO
        ~AvailableGames();
};

#endif