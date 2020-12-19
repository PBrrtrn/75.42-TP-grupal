#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "GameLoop.h"

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

GameLoop::GameLoop() 
: renderer("TEST", SCREEN_WIDTH, SCREEN_HEIGHT, render_events_queue) { 
  // TODO: Agregar ServerEventsReceiver a la MIL
}

GameLoop::~GameLoop() {
  SDL_Quit();
}

void GameLoop::run() {
  // this->serverEventsReceiver.start();
  this->render_events_queue.push(START);
  this->renderer.start();

  SDL_Event user_event;
  while (true) {
    auto start_t = std::chrono::steady_clock::now();
    SDL_PollEvent(&(user_event));
    if (user_event.type == SDL_QUIT) break;

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

    this->render_events_queue.push(CONTINUE);
    // encolar los eventos para enviarlos al servidor

    auto t = std::chrono::steady_clock::now() - start_t;
    auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);
    usleep((1000000/29) - sleep_t.count());
  }
}
