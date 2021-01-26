#include "action.h"
#include <iostream>

Action::Action(){}

void Action::tryAction(GameStatus& gs, int clientID) {}

bool Action:: is_colision(int clientID, Vector& next_position, GameStatus& gs) {
	
	Map& map = gs.map;
    if (map.isWall(next_position.getXCoordinate(), next_position.getYCoordinate())) {
		
        std::cout << "Wall detected - invalid move" << '\n';
        //TODO como imprimir mensaje en pantalla
        return true;
    } else if (/*agregar !isObject y funcion en map*/!3) {
        std::cout << "Object detected - invalid move" << '\n';
    } else {
        gs.setPosition(clientID, next_position);
        return false;
    }
} 

Action::~Action() {}
