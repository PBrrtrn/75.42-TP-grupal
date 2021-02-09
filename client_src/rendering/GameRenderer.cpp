#include "GameRenderer.h"

GameRenderer::GameRenderer(SDL_Renderer* renderer, YAML::Node config,
													 GameStatusMonitor& game_status_monitor) 
: renderer(renderer), config(config), game_status_monitor(game_status_monitor),
	map_drawer(config) {
	this->map = game_status_monitor.getMap();
	this->load();
}

GameRenderer::~GameRenderer() {
	for (Animation* animation : this->animations) delete animation;
  for (Texture* texture : this->wall_textures) delete texture;
}

void GameRenderer::load() {
	std::string walls_dir = config["walls"]["directory"].as<std::string>();

	for (int i = 0; i < this->config["walls"]["files"].size(); i++) {
	  std::string filename = this->config["walls"]["files"][i].as<std::string>();
	  std::string filepath = walls_dir + filename;

	  Texture* texture = new Texture(this->renderer, filepath.c_str());
	  this->wall_textures.push_back(texture);
	}
}

void GameRenderer::render() {
	SDL_RenderClear(this->renderer);

	GameStatusUpdate status_update = this->game_status_monitor.getUpdate();

	std::vector<float> z_buffer = map_drawer.draw(this->renderer, this->map,
																								status_update.position,
																								status_update.direction.getAngle(),
																								this->wall_textures);

	SDL_RenderPresent(this->renderer);
}