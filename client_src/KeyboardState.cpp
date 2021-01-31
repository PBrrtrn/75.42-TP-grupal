#include "KeyboardState.h"

KeyboardState::KeyboardState() {
  this->keyboard_state = {
    {SDLK_w, UP},
    {SDLK_a, UP},
    {SDLK_s, UP},
    {SDLK_d, UP}
  };
}

KeyboardState::~KeyboardState() { }

void KeyboardState::toggleKeyDown(int key) {
  this->keyboard_state[key] = DOWN;
}

void KeyboardState::toggleKeyUp(int key) {
  this->keyboard_state[key] = UP;
}

KeyState KeyboardState::isDown(int key) {
  return this->keyboard_state[key] == DOWN;
}