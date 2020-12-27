#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"
#include "ServerListener.h"
#include "GameStatus.h"
#include "GameStatusMonitor.h"
#include "Renderer.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

static const int FPS_CAP = 29;

GameLoop::GameLoop() {
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
  Renderer renderer("TEST", SCREEN_WIDTH, SCREEN_HEIGHT, game_status_monitor);
  /* TODO: Pasar al renderer una Configuración leída de un YAML que contenga los
     paths de las texturas, animaciones, etc. (actualmente hardoceados)
                              - Pablo (20/12/2020)                            */

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
    usleep((1000000/FPS_CAP) - sleep_t.count());
  }
}
