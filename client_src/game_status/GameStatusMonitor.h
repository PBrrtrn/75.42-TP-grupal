#ifndef __GAME_STATUS_MONITOR_H__
#define __GAME_STATUS_MONITOR_H__

#include <mutex>
#include <atomic>
#include <condition_variable>

#include "GameStatus.h"

class GameStatusMonitor {
private:
  GameStatus game_status;
  std::mutex mutex;
  std::condition_variable cv;
  bool synchronized;
  bool map_initialized;
  bool statistics_saved;
public:
  GameStatusMonitor();
  ~GameStatusMonitor();
  void initializeMap(Map& map);
  Map& getMap();
  void saveStatistics(GameStatistics& statistics);
  GameStatistics& getStatistics();
  void updateGameStatus(GameStatusUpdate& update);
  GameStatusUpdate getUpdate();
};

#endif