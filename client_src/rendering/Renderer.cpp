#include <iostream>
#include <unistd.h>
#include <array>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Texture.h"

static const int FOV = 1.0472;

Renderer::Renderer(YAML::Node& config, std::atomic<bool>& in_game, 
                   GameStatusMonitor& game_status_monitor,
                   MenuStatus& menu_status)
: renderer(NULL), config(config), window(config["window"]),
  in_game(in_game), game_status_monitor(game_status_monitor),
  menu_status(menu_status), fps_cap(config["FPS_cap"].as<int>()) {
  this->renderer = this->window.getRenderer();
  if (this->renderer == NULL) throw RendererConstructorError(SDL_GetError());

  SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    std::cout << "Warning: Could not set SDL hints" << std::endl;

  this->load();
}

Renderer::~Renderer() {
  for (Animation* animation : this->animations) delete animation;
  for (Texture* texture : this->wall_textures) delete texture;

  SDL_DestroyRenderer(this->renderer);
  IMG_Quit();
  this->join();
}

void Renderer::run() {
  while (true) {
    while (!this->in_game) renderMenu();

    Map map = this->game_status_monitor.getMap();
    MapDrawer map_drawer(this->config, this->wall_textures);
    while (this->in_game) renderMatch(map_drawer, map);
  }
}

void Renderer::renderMenu() {
  SDL_RenderClear(this->renderer);
  std::vector<GameOption> game_options = this->menu_status.getGameOptions();
  int selected_option = this->menu_status.getSelectedOption();

  std::cout << game_options.size() << std::endl;
  SDL_RenderPresent(this->renderer);
}

void Renderer::renderMatch(MapDrawer& map_drawer, Map& map) {
  SDL_RenderClear(this->renderer);

  SDL_RenderPresent(this->renderer);
}

/*
void Renderer::run() {
  Map map = this->game_status_monitor.getMap();
  MapDrawer map_drawer(this->config, this->wall_textures);

  int fps_cap = this->config["FPS_cap"].as<int>();

  while (true) {
    auto start_t = std::chrono::steady_clock::now();

    GameStatusUpdate status_update = this->game_status_monitor.getUpdate();
    if (!status_update.running) break;

    this->render(status_update, map_drawer, map);

    auto t = std::chrono::steady_clock::now() - start_t;
    auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);
    usleep((1000000/fps_cap) - sleep_t.count());
  }

  // Cerrar el programa de forma ordenada
}

void Renderer::render(GameStatusUpdate& status_update, 
                      MapDrawer& map_drawer, Map& map) {
  SDL_RenderClear(this->renderer);

  std::vector<float> z_buffer = map_drawer.draw(this->renderer, map,
                                                status_update.player_position,
                                                status_update.player_angle);

  // Hacer el resto del rendering

  SDL_RenderPresent(this->renderer);
}
*/

void Renderer::load() {
  std::string dir = config["walls"]["directory"].as<std::string>();

  for (int i = 0; i < this->config["walls"]["files"].size(); i++) {
    std::string filename = this->config["walls"]["files"][i].as<std::string>();
    std::string filepath = dir + filename;

    Texture* texture = new Texture(this->renderer, filepath.c_str());
    this->wall_textures.push_back(texture);
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
