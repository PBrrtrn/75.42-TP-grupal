#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>
#include <unordered_map>
#include <atomic>
#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "../game_status/GameStatusMonitor.h"
#include "../game_status/MenuStatus.h"
#include "Window.h"
#include "PlayerWeapon.h"
#include "Font.h"
#include "EnemyComponent.h"
#include "EnemyEntity.h"
#include "Texture.h"
#include "MapDrawer.h"
#include "UIDrawer.h"
#include "MusicTrack.h"
#include "../../common_src/Map.h"
#include "../../common_src/Thread.h"

class Renderer : public Thread {
private:
  SDL_Renderer* renderer;
  YAML::Node& config;
  Window window;
  std::atomic<bool>& in_game;
  std::atomic<bool> running;
  GameStatusMonitor& game_status_monitor;
  MenuStatus& menu_status;
  int fps_cap;
  std::vector<Texture*> wall_textures;
  std::vector<Texture*> item_textures;
  std::vector<EnemyComponent*> enemy_components;
  std::vector<PlayerWeapon*> player_weapons;
  MusicTrack* menu_music;
  MusicTrack* game_music;
  std::unordered_map<char, EnemyEntity*> enemies;
  void load();
  void renderMatch(MapDrawer& map_drawer, UIDrawer& ui_drawer);
public:
  Renderer(YAML::Node& config, std::atomic<bool>& in_game, 
           GameStatusMonitor& game_status_monitor,
           MenuStatus& menu_status);
  ~Renderer();
  void run();
  void stop();
  void toggleFullscreen();
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
