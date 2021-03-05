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

    int x_grid = (int)next_position.x;
    int y_grid = (int)next_position.y;

    if (map.isWall(x_grid, y_grid)) {
        return true;
    } else if (map.isObstacle(next_position)) {
        return true;
    } else if (gs.isPlayer(next_position)) {
        return true;
    } else {
        gs.setPosition(clientID, next_position);
        return false;
    }
} 

Action::~Action() {}
