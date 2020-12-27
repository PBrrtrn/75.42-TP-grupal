#include <iostream>
#include <unistd.h>
#include <SDL2/SDL_image.h>

#include "Renderer.h"
#include "Texture.h"

static const int FPS_CAP = 29;

Renderer::Renderer(const char* title, const int width, const int height,
                   GameStatusMonitor& game_status_monitor) 
: renderer(NULL), window(title, width, height), 
  game_status_monitor(game_status_monitor) {
  /* No me vuelve loco la idea de tener que estar haciendo pasamano de los
    atributos de Window. Capaz sería mejor inicializar la ventana desde
    afuera en el GameLoop y pasarla por movimiento para que el Renderer
    tenga ownership sin necesitar saber crearla. 
                                            - Pablo (06/12/2020)        */
  this->renderer = this->window.getRenderer();
  if (this->renderer == NULL) throw RendererConstructorError(SDL_GetError());

  SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    std::cout << "Warning: Could not set SDL hints" << std::endl;
}

Renderer::~Renderer() {
  for (Animation* animation : this->animations) delete animation;

  SDL_DestroyRenderer(this->renderer);
  IMG_Quit();
  this->join();
}

void Renderer::run() {
  this->load();
  while (true) {
    auto start_t = std::chrono::steady_clock::now();

    GameStatusUpdate status_update = this->game_status_monitor.getUpdate();
    if (!status_update.running) break;
    this->render(status_update);

    auto t = std::chrono::steady_clock::now() - start_t;
    auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);
    usleep((1000000/FPS_CAP) - sleep_t.count());
  }

  // Tomar las acciones que sean necesarias para cerrar el programa.
}

void Renderer::render(GameStatusUpdate& status_update) {
  SDL_RenderClear(this->renderer);

  for (Animation* animation : this->animations) {
    animation->renderNextFrame(this->renderer, 1, 0, 0);
  }

  // Hacer el resto del rendering

  SDL_RenderPresent(this->renderer);
}

void Renderer::load() {
  /* TODO: Por el momento solo se carga una animación al vector para poder
  testear. Acá habría que cargar todas las animaciones, texturas, etc.
  recibiendo sus paths y dimensiones desde una clase Config que las cargue
  desde el YML. Si, estoy programando en Navidad.
                                      - Pablo (25/12/2020)              */
  this->map = this->game_status_monitor.getMap();

  Animation* animation = new Animation(this->renderer, "foo.png", 64, 205, 4);
  this->animations.push_back(animation);
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
