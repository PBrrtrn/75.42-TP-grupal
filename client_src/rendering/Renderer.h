#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include <atomic>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "../game_status/GameStatusMonitor.h"
#include "../game_status/MenuStatus.h"
#include "MenuRenderer.h"
#include "Window.h"
#include "Font.h"
#include "Animation.h"
#include "Texture.h"
#include "MapDrawer.h"
#include "../../common_src/Map.h"
#include "../../common_src/Thread.h"

class Renderer : public Thread {
private:
  SDL_Renderer* renderer;
  YAML::Node& config;
  Window window;
  std::atomic<bool>& in_game;
  GameStatusMonitor& game_status_monitor;
  MenuStatus& menu_status;
  int fps_cap;
  std::vector<Animation*> animations;
  std::vector<Texture*> wall_textures;
  void load();
  void renderMatch(MapDrawer& map_drawer, Map& map);
public:
  Renderer(YAML::Node& config, std::atomic<bool>& in_game, 
           GameStatusMonitor& game_status_monitor,
           MenuStatus& menu_status);
  ~Renderer();
  void run();
};

#define ERROR_BUF_LEN 256

class RendererConstructorError : public std::exception {
private:
  char error_msg[ERROR_BUF_LEN];
public:
  explicit RendererConstructorError(const char* sdl_error) noexcept;
  virtual const char* what() const noexcept;
  virtual ~RendererConstructorError() noexcept;
};

#endif
