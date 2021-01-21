#include <iostream>
#include <unistd.h>
#include <array>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Texture.h"

static const int FPS_CAP = 29;
static const int FOV = 1.0472;

Renderer::Renderer(const char* title, const int width, const int height,
                   GameStatusMonitor& game_status_monitor) 
: renderer(NULL), window(title, width, height), 
  game_status_monitor(game_status_monitor) {
  /* Update: El titulo y la resolución, así como el FOV, eventualmente van a
    llegar por YML así que no estaría mal pasarle los parámetros al Renderer 
                                            - Pablo (06/12/2020)        */
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
  Map map = this->game_status_monitor.getMap();
  MapDrawer map_drawer(this->window.getWidth(),
                       this->window.getHeight(),
                       FOV, this->wall_textures);
  while (true) {
    auto start_t = std::chrono::steady_clock::now();

    GameStatusUpdate status_update = this->game_status_monitor.getUpdate();
    if (!status_update.running) break;

    this->render(status_update, map_drawer, map);

    auto t = std::chrono::steady_clock::now() - start_t;
    auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);
    usleep((1000000/FPS_CAP) - sleep_t.count());
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

void Renderer::load() {
  /* TODO: Por el momento solo se carga una animación al vector para poder
  testear. Acá habría que cargar todas las animaciones, texturas, etc.
  recibiendo sus paths y dimensiones desde una clase Config que las cargue
  desde el YML. Si, estoy programando en Navidad.
                                      - Pablo (25/12/2020)              */
  Texture *texture = new Texture(this->renderer, "../assets/textures/wood.png");
  this->wall_textures.push_back(texture);
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
