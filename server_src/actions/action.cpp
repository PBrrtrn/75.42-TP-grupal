#include "action.h"
#include <iostream>

Action::Action(){}

void Action::tryAction(GameStatus& gs, int clientID, Map& map) {}

bool Action:: is_colision(int clientID, Vector& next_position, Map& map, GameStatus& gs) {
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
