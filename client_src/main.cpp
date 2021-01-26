#include <iostream>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"

int main(int argc, char *argv[]) {

	std::cout << "voy a abrir la config" << std::endl;
	YAML::Node config = YAML::LoadFile("../config/client_config.yml");
	std::cout << "abri config" << std::endl;

  GameLoop game_loop(config);
  game_loop.run();
}
