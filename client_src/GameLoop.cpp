#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"
#include "ServerListener.h"
#include "GameStatus.h"
#include "GameStatusMonitor.h"
#include "Renderer.h"

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
  GameStatusMonitor game_status_monitor;
  ServerListener server_listener(game_status_monitor);
  Renderer renderer(this->config, game_status_monitor);

  int fps_cap = this->config["FPS_cap"].as<int>();

  server_listener.start();
  renderer.start();

  SDL_Event user_event;
  while (true) {
    auto start_t = std::chrono::steady_clock::now();
    SDL_PollEvent(&(user_event));
    if (user_event.type == SDL_QUIT) throw 1;

    switch (user_event.type) {
      case (SDL_KEYDOWN) : 
        this->keyboard_state.toggleKeyDown(user_event.key.keysym.sym);
        break;
      case (SDL_KEYUP) :
        this->keyboard_state.toggleKeyUp(user_event.key.keysym.sym);
        break;
    }

    if (this->keyboard_state.isDown(SDLK_w)) {
      std::cout << "Move up" << std::endl;
    } else if (this->keyboard_state.isDown(SDLK_s)) {
      std::cout << "Move down" << std::endl;
    } else if (this->keyboard_state.isDown(SDLK_a)) {
      std::cout << "Move left" << std::endl;
    } else if (this->keyboard_state.isDown(SDLK_d)) {
      std::cout << "Move right" << std::endl;
    }

    // encolar los eventos para enviarlos al servidor

    auto t = std::chrono::steady_clock::now() - start_t;
    auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);

    usleep((1000000/fps_cap) - sleep_t.count());
  }
}