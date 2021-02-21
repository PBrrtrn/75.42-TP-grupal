#include <iostream>
#include <atomic>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"

#include "ServerConnection.h"
#include "game_status/MenuStatus.h"
#include "game_status/GameStatusMonitor.h"
#include "event_handling/InputHandler.h"
#include "event_handling/StatusUpdater.h"
#include "event_handling/Request.h"
#include "rendering/Renderer.h"
#include "../common_src/blocking_queue.h"

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

  MenuStatus menu_status;
  GameStatusMonitor game_status_monitor;

  std::atomic<bool> in_game(false);

  BlockingQueue<UserRequest> request_queue;

  std::string host = this->config["server"]["host"].as<std::string>();
  std::string port = this->config["server"]["port"].as<std::string>();
  ServerConnection server_connection(host, port);

  InputHandler input_handler(in_game, menu_status, request_queue);

  EventSender event_sender(in_game, request_queue, server_connection);
  UpdateReceiver update_receiver(in_game, server_connection,
                                 game_status_monitor,
                                 menu_status);

  Renderer renderer(this->config, in_game, game_status_monitor, menu_status);

  event_sender.start();
  update_receiver.start();
  renderer.start();

  SDL_Event user_input;
  while (true) {
    auto start_t = std::chrono::steady_clock::now();

    while (SDL_PollEvent(&user_input)) {
      if (user_input.type == SDL_QUIT) {
        // TODO: Salir de forma ordenada
        throw 1;
      }
      input_handler.process(user_input);
    }

    auto t = std::chrono::steady_clock::now() - start_t;
    auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);

    usleep((1000000/fps_cap) - sleep_t.count());
  }
}
