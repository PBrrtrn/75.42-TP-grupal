#include <iostream>
#include "StatisticsRenderer.h"

StatisticsRenderer::StatisticsRenderer(YAML::Node config, SDL_Renderer* renderer, GameStatistics& statistics): 
    config(config),
    renderer(renderer), 
	statistics(statistics)
{
	this->load();
}

StatisticsRenderer::~StatisticsRenderer() {
	delete this->background;
	delete this->font;
}

void StatisticsRenderer::load() {
	std::string dir = config["directory"].as<std::string>();

  std::string background = config["background"].as<std::string>();
  std::string background_path = dir + background;
  this->background = new Texture(this->renderer, background_path.c_str());

  std::string font = config["font"].as<std::string>();
  std::string font_path = dir + font;
  this->font = new Font(font_path.c_str());
}

void StatisticsRenderer::render() {
	SDL_RenderClear(this->renderer);

	this->background->render(this->renderer, NULL, NULL);

	this->renderStatisticsBox();

	SDL_RenderPresent(this->renderer);
}

void StatisticsRenderer::renderStatisticsBox() {
	int box_x = this->config["statistics_box"]["x_pos"].as<int>();
	int box_y = this->config["statistics_box"]["x_pos"].as<int>();
	int box_w = this->config["statistics_box"]["width"].as<int>();
	int box_h = this->config["statistics_box"]["height"].as<int>();

	int gilding_w = this->config["statistics_box"]["gilding"].as<int>();

	SDL_Rect statistics_box { box_x, box_y, box_w, box_h };

	SDL_Rect outer_gilding { box_x - gilding_w * 2, box_y - gilding_w * 2, 
							box_w + gilding_w * 4, box_h + gilding_w * 4 };

	SDL_SetRenderDrawColor(this->renderer, 255, 223, 0, 0);
	SDL_RenderFillRect(this->renderer, &outer_gilding);

	SDL_Rect inner_gilding { box_x - gilding_w, box_y - gilding_w, 
							box_w + gilding_w * 2, box_h + gilding_w * 2 };

	SDL_SetRenderDrawColor(this->renderer, 200, 173, 0, 0);
	SDL_RenderFillRect(this->renderer, &inner_gilding);

	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);

	SDL_Color text_color { 255, 255, 255 };

	int kills_x = config["kills"]["x_pos"].as<int>();
	int kills_y = config["kills"]["y_pos"].as<int>();
	std::stringstream kills_stream;
	kills_stream << config["kills"]["text"].as<std::string>();
	for (auto k : statistics.kills) {
		kills_stream << k.clientId << "-" << k.kills << "/";
	}
	std::string kills = kills_stream.str();

	this->font->render(this->renderer, kills.c_str(), 
										kills_x, kills_y, 1, text_color);

	int points_x = config["points"]["x_pos"].as<int>();
	int points_y = config["points"]["y_pos"].as<int>();
	std::stringstream points_stream;
	points_stream << config["points"]["text"].as<std::string>();
	for (auto p : statistics.points) {
		points_stream << p.clientId << "-" << p.puntaje << "/";
	}
	std::string points = points_stream.str();

	this->font->render(this->renderer, points.c_str(), 
										points_x, points_y, 1, text_color);

	int shot_bullets_x = config["shot_bullets"]["x_pos"].as<int>();
	int shot_bullets_y = config["shot_bullets"]["y_pos"].as<int>();
	std::stringstream shot_bullets_stream;
	shot_bullets_stream << config["shot_bullets"]["text"].as<std::string>();
	for (auto p : statistics.bullets) {
		shot_bullets_stream << p.clientId << "-" << p.bullets_shooted << "/";
	}
	std::string shot_bullets = shot_bullets_stream.str();

	this->font->render(this->renderer, shot_bullets.c_str(), 
										shot_bullets_x, shot_bullets_y, 1, text_color);
}

