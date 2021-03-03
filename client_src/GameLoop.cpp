#include <iostream>
#include <atomic>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"

#include "ServerConnection.h"
#include "game_status/MenuStatus.h"
#include "game_status/GameStatusMonitor.h"
#include "event_handling/InputHandler.h"
#include "event_handling/EventSender.h"
#include "event_handling/UpdateReceiver.h"
#include "rendering/Renderer.h"
#include "../common_src/blocking_queue.h"
#include "../common_src/MessageType.h"

GameLoop::GameLoop(YAML::Node& config) : config(config) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("Failed to initialize SDL");
    // throw SDLInitializationError(SDL_GetError());
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    std::cout << "Warning: Could not set render scale quality" << std::endl;
}

GameLoop::~GameLoop() {
  SDL_Quit();
}

void GameLoop::run() {
  int fps_cap = this->config["FPS_cap"].as<int>();

  std::string host = this->config["server"]["host"].as<std::string>();
  std::string port = this->config["server"]["port"].as<std::string>();
  ServerConnection server_connection(host, port);

  MenuStatus menu_status;
  GameStatusMonitor game_status_monitor;

  BlockingQueue<ClientMessage> message_queue;

  std::atomic<bool> in_game(false);

  EventSender event_sender(message_queue, server_connection);
  UpdateReceiver update_receiver(in_game, server_connection,
                                 game_status_monitor,
                                 menu_status);

  Renderer renderer(this->config, in_game, game_status_monitor, menu_status);

  InputHandler input_handler(in_game, menu_status, message_queue);

  event_sender.start();
  update_receiver.start();
  renderer.start();

  SDL_Event input;
  while (true) {
    try {
      SDL_WaitEvent(&input);
    } catch (...) {
      // throw ...
    }
    SDL_Keycode code = input.key.keysym.sym;

    if (input.type == SDL_QUIT) {
      throw 1;
    } else if ((input.type == SDL_KEYDOWN) && (code == SDLK_f)) {
      renderer.toggleFullscreen();
    } else {
      input_handler.process(input);
    }
  }
}
