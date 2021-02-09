#include "action.h"
#include <iostream>
#include <math.h>

Action::Action(){
    const YAML::Node& c = ServerConfig::Config["Moves"];
    this->step = c["Step"].as<float>();
    this->rotation_left = c["RotationLeft"].as<float>();
    this->rotation_right = c["RotationRight"].as<float>();
}

void Action::tryAction(GameStatus& gs, int clientID) {}

bool Action:: is_colision(int clientID, Vector& next_position, GameStatus& gs) {
	MapServer& map = gs.map;

    double x_grid;
    modf(next_position.getXCoordinate(), &x_grid);
    double y_grid;
    modf(next_position.getYCoordinate(), &y_grid);
    
    if (map.isWall((int) x_grid, (int) y_grid)) {
        std::cout << "Wall detected - invalid move" << '\n';
        //TODO como imprimir mensaje en pantalla
        return true;
    } else if (map.isObstacle(next_position)) {
        std::cout << "Object detected - invalid move" << '\n';
        return true;
    } else {
        gs.setPosition(clientID, next_position);
        return false;
    }
} 

Action::~Action() {}
