#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include "KeyboardState.h"

class GameLoop {
private:
  KeyboardState keyboard_state;
public:
  GameLoop();
  ~GameLoop();
  void run();
};

#endif