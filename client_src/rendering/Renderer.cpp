#include <iostream>
#include <sstream>
#include <unistd.h>
#include <array>
#include <SDL2/SDL_image.h>

#include "Renderer.h"

Renderer::Renderer(YAML::Node& config, std::atomic<bool>& in_game, 
                   GameStatusMonitor& game_status_monitor,
                   MenuStatus& menu_status)
: renderer(NULL), config(config), window(config["window"]),
  in_game(in_game), game_status_monitor(game_status_monitor),
  menu_status(menu_status), fps_cap(config["FPS_cap"].as<int>()) {
  this->renderer = this->window.getRenderer();
  if (this->renderer == NULL) throw RendererConstructorError(SDL_GetError());

  if (TTF_Init() == -1) throw RendererConstructorError(TTF_GetError());

  SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    std::cout << "Warning: Could not set SDL hints" << std::endl;
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(this->renderer);
  TTF_Quit();
  IMG_Quit();
  this->join();
}

void Renderer::run() {
  while (true) {
    {
      MenuRenderer menu_renderer(this->config["menu_ui"], 
                                 this->menu_status,
                                 this->renderer);
      while (!this->in_game) menu_renderer.render();
    }

    {
      GameRenderer game_renderer(this->renderer, this->config,
                                 this->game_status_monitor);
      while (this->in_game) {
        auto start_t = std::chrono::steady_clock::now();

        game_renderer.render();

        auto t = std::chrono::steady_clock::now() - start_t;
        auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);
        usleep((1000000/fps_cap) - sleep_t.count());
      } 
    }
  }
}

RendererConstructorError::RendererConstructorError
                (const char *sdl_error) noexcept {
  snprintf(this->error_msg, ERROR_BUF_LEN, 
           "Failed to initialize SDL_Renderer: %s", sdl_error);
}

RendererConstructorError::~RendererConstructorError() noexcept { }

const char* RendererConstructorError::what() const noexcept {
  return this->error_msg;
}
