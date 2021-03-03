#include <iostream>
#include <sstream>
#include <unistd.h>
#include <array>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Renderer.h"
#include "MenuRenderer.h"
#include "../../common_src/FiringState.h"

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

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    throw RendererConstructorError(Mix_GetError());

  this->load();
}

Renderer::~Renderer() {
  for (Animation* animation : this->enemy_animations) delete animation;
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

  YAML::Node weapons_node = this->config["animations"]["weapons"];
  for (int i = 0; i < weapons_node.size(); i++) {
    PlayerWeapon* player_weapon = new PlayerWeapon(weapons_node[i], 
                                                   this->renderer);
    this->player_weapons.push_back(player_weapon);
  }

  YAML::Node music_node = this->config["music"];
  

  //////////////////////////////////////////////////////////////
  std::vector<std::string> paths;
  paths.push_back(std::string("../assets/sprites/enemies/ss/idle_front.png"));

  Animation* animation = new Animation(this->renderer, paths);
  this->enemy_animations.push_back(animation);
  //////////////////////////////////////////////////////////////
}

void Renderer::run() {
  while (true) {
    MenuRenderer menu_renderer(this->config["menu_ui"],
                               this->menu_status,
                               this->renderer);
    while (!this->in_game) menu_renderer.render();

    Map map = this->game_status_monitor.getMap();
    MapDrawer map_drawer(this->config, map, 
                         this->wall_textures, 
                         this->enemy_animations);
    UIDrawer ui_drawer(this->renderer, this->config["game_ui"]);
    while (this->in_game) renderMatch(map_drawer, ui_drawer);
  }
}

void Renderer::renderMatch(MapDrawer& map_drawer, UIDrawer& ui_drawer) {
  SDL_RenderClear(this->renderer);

  GameStatusUpdate status_update = this->game_status_monitor.getUpdate();

  map_drawer.draw(this->renderer, status_update.position, 
                  status_update.direction.getAngle(),
                  status_update.enemies, status_update.items);

  int selected_weapon = int(status_update.selected_weapon);
  if (status_update.player_firing == STATE_FIRING)
    this->player_weapons[selected_weapon]->setShooting();
  this->player_weapons[selected_weapon]->render(this->renderer);

  ui_drawer.draw(this->renderer, status_update.health, 
                 status_update.enemies.size(), status_update.bullets,
                 status_update.lives, status_update.has_key);

  SDL_RenderPresent(this->renderer);
}

void Renderer::toggleFullscreen() {
  this->window.toggleFullscreen();
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
