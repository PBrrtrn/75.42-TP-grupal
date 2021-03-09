#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include <yaml-cpp/yaml.h>
#include <atomic>

class GameLoop {
private:
	YAML::Node& config;
  std::atomic<bool> keep_running{true};
public:
  GameLoop(YAML::Node& config);
  ~GameLoop();
  void shutdown();
  void run();
};

#endif