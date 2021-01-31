#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include <yaml-cpp/yaml.h>

class GameLoop {
private:
	YAML::Node& config;
public:
  GameLoop(YAML::Node& config);
  ~GameLoop();
  void run();
};

#endif