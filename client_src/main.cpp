#include <iostream>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"

int main(int argc, char *argv[]) {
	YAML::Node config = YAML::LoadFile("../config/client_config.yml");

  GameLoop game_loop(config);
  game_loop.run();
}
