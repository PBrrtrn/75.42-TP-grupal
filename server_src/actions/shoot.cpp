#include "action.h"
#include "shoot.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){

    for (auto& it: gs.players) {
        int id = it.first;
		//if (gs.getPosition(id)) {
			//this->players.at(clientId) 
		//}
        //int gameId = this->clientsInGames.at(it.first);
        //TODO: chequear tiempo de ejecucion -- eficiencia pasaje gamestatus
        //this->out_queues.at(clientId)->push(this->games.at(gameId)->getGameStatus());
    }
}

Shoot::~Shoot() {}
