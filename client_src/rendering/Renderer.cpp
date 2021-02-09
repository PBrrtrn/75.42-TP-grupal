#include <iostream>
#include <sstream>
#include <unistd.h>
#include <array>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "MenuRenderer.h"

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

  this->load();
}

Renderer::~Renderer() {
  for (Animation* animation : this->animations) delete animation;
  for (Texture* texture : this->wall_textures) delete texture;

  SDL_DestroyRenderer(this->renderer);
  TTF_Quit();
  IMG_Quit();
  this->join();
}

void Renderer::load() {
  std::string walls_dir = config["walls"]["directory"].as<std::string>();

  for (int i = 0; i < this->config["walls"]["files"].size(); i++) {
    std::string filename = this->config["walls"]["files"][i].as<std::string>();
    std::string filepath = walls_dir + filename;

    Texture* texture = new Texture(this->renderer, filepath.c_str());
    this->wall_textures.push_back(texture);
  }
}

void Renderer::run() {
  while (true) {
    MenuRenderer menu_renderer(this->config["menu_ui"],
                               this->menu_status,
                               this->renderer);
    while (!this->in_game) menu_renderer.render();

    Map map = this->game_status_monitor.getMap();
    MapDrawer map_drawer(this->config, this->wall_textures);
    while (this->in_game) renderMatch(map_drawer, map);
  }
}

void Renderer::renderMatch(MapDrawer& map_drawer, Map& map) {
  SDL_RenderClear(this->renderer);

  GameStatusUpdate u = this->game_status_monitor.getUpdate();

  std::vector<float> z_buffer = map_drawer.draw(this->renderer, map,
                                                u.position,
                                                u.direction.getAngle());

  SDL_RenderPresent(this->renderer);
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
