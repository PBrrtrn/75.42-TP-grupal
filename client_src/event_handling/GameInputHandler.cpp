#include "GameInputHandler.h"

#include <unordered_map>
#include "../../common_src/MessageType.h"

static std::unordered_map<SDL_Keycode, MessageType> keydown_map = {
  { SDLK_w, TYPE_MOVE_FORWARD_START },
  { SDLK_a, TYPE_MOVE_LEFT_START },
  { SDLK_s, TYPE_MOVE_BACKWARD_START },
  { SDLK_d, TYPE_MOVE_RIGHT_START },
  { SDLK_1, TYPE_CHANGE_CUCHILLO },
  { SDLK_2, TYPE_CHANGE_PISTOLA },
  { SDLK_3, TYPE_CHANGE_AMETRALLADORA },
  { SDLK_4, TYPE_CHANGE_CANION },
  { SDLK_SPACE, TYPE_SHOOT_START }
};

static std::unordered_map<SDL_Keycode, MessageType> keyup_map = {
  { SDLK_w, TYPE_MOVE_FORWARD_STOP },
  { SDLK_a, TYPE_MOVE_LEFT_STOP },
  { SDLK_s, TYPE_MOVE_BACKWARD_STOP },
  { SDLK_d, TYPE_MOVE_RIGHT_STOP },
  { SDLK_SPACE, TYPE_SHOOT_STOP }
};

GameInputHandler::GameInputHandler(BlockingQueue<ClientMessage>& message_queue)
: message_queue(message_queue) { }

GameInputHandler::~GameInputHandler() { }

void GameInputHandler::handle(SDL_Event input) {
  if (input.key.repeat == 0) {
    SDL_Keycode keycode = input.key.keysym.sym;
    bool keydown = this->keyboard_state.isDown(keycode);
    if ((input.type == SDL_KEYDOWN) && (!keydown)) {
      ClientMessage message { keydown_map[keycode] };
      this->message_queue.push(message);
      this->keyboard_state.toggleKeyDown(keycode);
    } else if ((input.type == SDL_KEYUP) && (keydown)) {
      ClientMessage message { keyup_map[keycode] };
      this->message_queue.push(message);
      this->keyboard_state.toggleKeyUp(keycode);
    }
  }
}
