#include "use_door.h"

UseDoor::UseDoor(){}
void UseDoor::tryAction(GameStatus& gs, int clientID){
	Vector player_position = gs.playersPositions.at(clientID);
	for (auto& it: gs.doors) {
		Door& door = it.second;
		float distance = (player_position - door.getLocation()).norm();
		//la llave del jugador se consume al hacer useKey exitoso.
		if ( distance < 1 && (!door.isLocked() || (door.isLocked() && gs.players.at(clientID).useKey()))) {
			//abrir el cerrojo de la puerta. Si no estaba con llave, no hace nada.
			door.unlockDoor();
			//abre la puerta propiamente dicha
			door.openDoor();
			
		}
	}
}
UseDoor::~UseDoor(){}
