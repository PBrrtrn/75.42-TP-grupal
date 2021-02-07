#include "action.h"
#include <iostream>
#include <math.h>

Action::Action(){
    const YAML::Node& c = ServerConfig::Config["Moves"];
    this->step = c["Step"].as<int>();
    this->rotation_left = c["RotationLeft"].as<int>();
    this->rotation_right = c["RotationRight"].as<int>();
}

void Action::tryAction(GameStatus& gs, int clientID) {}

bool Action:: is_colision(int clientID, Vector& next_position, GameStatus& gs) {
	MapServer& map = gs.map;

    double x_grid;
    modf(next_position.getXCoordinate() / map.getWidth(), &x_grid);
    double y_grid;
    modf(next_position.getYCoordinate() / map.getHeight(), &y_grid);
    
    if (map.isWall((int) x_grid, (int) y_grid)) {
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
