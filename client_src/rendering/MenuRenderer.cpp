#include <iostream>
#include "MenuRenderer.h"

#include "../../common_src/ClientGameStatusElements.h"

MenuRenderer::MenuRenderer(YAML::Node config,
													 MenuStatus& menu_status,
													 SDL_Renderer* renderer)
: config(config), menu_status(menu_status), renderer(renderer) {
	this->load();
}

MenuRenderer::~MenuRenderer() {
	delete this->background;
	delete this->font;
}

void MenuRenderer::load() {
	std::string dir = config["directory"].as<std::string>();

  std::string background = config["background"].as<std::string>();
  std::string background_path = dir + background;
  this->background = new Texture(this->renderer, background_path.c_str());

  std::string font = config["font"].as<std::string>();
  std::string font_path = dir + font;
  this->font = new Font(font_path.c_str());
}

void MenuRenderer::render() {
	SDL_RenderClear(this->renderer);

	this->background->render(this->renderer, NULL, NULL);

	int selected_option = this->menu_status.getSelectedOption();
	if (this->menu_status.getCurrentScreen() == GAME_SELECTION) {
		this->renderGamesBox(selected_option);

		SDL_Color new_game_text_color { 255, 255, 255 };
		if (selected_option == 0) {
		  new_game_text_color.g = 69;
		  new_game_text_color.b = 0;
		}
		this->font->render(this->renderer, "HOST NEW", 200, 
		                   420, 1, new_game_text_color);

		SDL_Color refresh_text_color { 255, 255, 255 };
		if (selected_option == 1) {
		  refresh_text_color.g = 69;
		  refresh_text_color.b = 0;
		}
		this->font->render(this->renderer, "REFRESH", 400, 
		                   420, 1, refresh_text_color);
	} else if (this->menu_status.getCurrentScreen() == GAME_CREATION) {
		this->renderMapsBox(selected_option);

		SDL_Color back_text_color { 255, 255, 255 };
		if (selected_option == 0) {
		  back_text_color.g = 69;
		  back_text_color.b = 0;
		}
		this->font->render(this->renderer, "BACK", 300, 
		                   420, 1, back_text_color);
	} else if (this->menu_status.getCurrentScreen() == LOBBY) {
		this->renderLobbyBox(this->menu_status.getLobbyStatus());
	} else {
    this->renderStatisticsScreen();
  }

	SDL_RenderPresent(this->renderer);
}

void MenuRenderer::renderGamesBox(int selected_option) {
	int box_x = this->config["matches_box"]["x_pos"].as<int>();
  int box_y = this->config["matches_box"]["x_pos"].as<int>();
  int box_w = this->config["matches_box"]["width"].as<int>();
  int box_h = this->config["matches_box"]["height"].as<int>();

  int gilding_w = this->config["matches_box"]["gilding"].as<int>();

  SDL_Rect matches_box { box_x, box_y, box_w, box_h };

  SDL_Rect outer_gilding { box_x - gilding_w * 2, box_y - gilding_w * 2, 
                           box_w + gilding_w * 4, box_h + gilding_w * 4 };

  SDL_SetRenderDrawColor(this->renderer, 255, 223, 0, 0);
  SDL_RenderFillRect(this->renderer, &outer_gilding);

  SDL_Rect inner_gilding { box_x - gilding_w, box_y - gilding_w, 
                           box_w + gilding_w * 2, box_h + gilding_w * 2 };

  SDL_SetRenderDrawColor(this->renderer, 200, 173, 0, 0);
  SDL_RenderFillRect(this->renderer, &inner_gilding);

  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(this->renderer, &matches_box);

  std::vector<GameListItem> game_options = this->menu_status.getGameOptions();
  int text_y = box_y + 25;
  int i = 0;
  while ((i < game_options.size()) && (text_y < box_y + box_h) ) {
    bool highlight = (selected_option - 2 == i);
    renderGameOption(game_options[i], text_y, highlight);

    i++;
    text_y += 35;
  }
}

void MenuRenderer::renderMapsBox(int selected_option) {
	int box_x = this->config["maps_box"]["x_pos"].as<int>();
  int box_y = this->config["maps_box"]["x_pos"].as<int>();
  int box_w = this->config["maps_box"]["width"].as<int>();
  int box_h = this->config["maps_box"]["height"].as<int>();

  int gilding_w = this->config["maps_box"]["gilding"].as<int>();

  SDL_Rect maps_box { box_x, box_y, box_w, box_h };

  SDL_Rect outer_gilding { box_x - gilding_w * 2, box_y - gilding_w * 2, 
                           box_w + gilding_w * 4, box_h + gilding_w * 4 };

  SDL_SetRenderDrawColor(this->renderer, 255, 223, 0, 0);
  SDL_RenderFillRect(this->renderer, &outer_gilding);

  SDL_Rect inner_gilding { box_x - gilding_w, box_y - gilding_w, 
                           box_w + gilding_w * 2, box_h + gilding_w * 2 };

  SDL_SetRenderDrawColor(this->renderer, 200, 173, 0, 0);
  SDL_RenderFillRect(this->renderer, &inner_gilding);

  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(this->renderer, &maps_box);

  std::vector<MapListItem> map_options = this->menu_status.getMapOptions();
  int text_y = box_y + 25;
  int i = 0;
  while ((i < map_options.size()) && (text_y < box_y + box_h) ) {
    bool highlight = (selected_option - 1 == i);
    renderMapOption(map_options[i], text_y, highlight);

    i++;
    text_y += 35;
  }
}

void MenuRenderer::renderLobbyBox(LobbyStatusData lobby_status) {
	YAML::Node node = this->config["lobby_box"];
	int box_x = node["x_pos"].as<int>();
  int box_y = node["x_pos"].as<int>();
  int box_w = node["width"].as<int>();
  int box_h = node["height"].as<int>();

  int gilding_w = node["gilding"].as<int>();

  SDL_Rect lobby_box { box_x, box_y, box_w, box_h };

  SDL_Rect outer_gilding { box_x - gilding_w * 2, box_y - gilding_w * 2, 
                           box_w + gilding_w * 4, box_h + gilding_w * 4 };

  SDL_SetRenderDrawColor(this->renderer, 255, 223, 0, 0);
  SDL_RenderFillRect(this->renderer, &outer_gilding);

  SDL_Rect inner_gilding { box_x - gilding_w, box_y - gilding_w, 
                           box_w + gilding_w * 2, box_h + gilding_w * 2 };

  SDL_SetRenderDrawColor(this->renderer, 200, 173, 0, 0);
  SDL_RenderFillRect(this->renderer, &inner_gilding);

  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
  SDL_RenderFillRect(this->renderer, &lobby_box);

  int back_text_x = node["back_text"]["x_pos"].as<int>();
  int back_text_y = node["back_text"]["y_pos"].as<int>();
  std::string back_text = node["back_text"]["text"].as<std::string>();

  SDL_Color back_text_color { 255, 69, 0 };

  this->font->render(this->renderer, back_text.c_str(), 
  									 back_text_x, back_text_y, 
  									 1, back_text_color);

  int header_text_x = node["header_text"]["x_pos"].as<int>();
  int header_text_y = node["header_text"]["y_pos"].as<int>();
  std::string header_text = node["header_text"]["text"].as<std::string>();

  SDL_Color text_color { 255, 255, 255 };

  this->font->render(this->renderer, header_text.c_str(), 
  									 header_text_x, header_text_y, 1, text_color);

  int time_text_x = node["time_text"]["x_pos"].as<int>();
  int time_text_y = node["time_text"]["y_pos"].as<int>();
  std::stringstream time_stream;
  time_stream << node["time_text"]["text"].as<std::string>();
  time_stream << lobby_status.remainingTime;
  time_stream << " seconds";
  std::string time_text = time_stream.str();

  this->font->render(this->renderer, time_text.c_str(), 
  									 time_text_x, time_text_y, 1, text_color);

  int players_text_x = node["players_text"]["x_pos"].as<int>();
  int players_text_y = node["players_text"]["y_pos"].as<int>();
  std::stringstream players_stream;
  players_stream << node["players_text"]["text"].as<std::string>();
  players_stream << lobby_status.players;
  players_stream << "/";
  players_stream << lobby_status.maxPlayers;
  std::string players_text = players_stream.str();

  this->font->render(this->renderer, players_text.c_str(), 
  									 players_text_x, players_text_y, 1, text_color);
}

void MenuRenderer::renderGameOption(GameListItem& option, 
																		int y, bool highlight) {
	std::stringstream stream;
	// Agregar al stream el nombre del mapa
	stream << "(";
	stream << int(option.players);
	stream << "/";
	stream << int(option.maxPlayers);
	stream << ")";
	std::string text = stream.str();

	SDL_Color match_text_color { 255, 255, 255 };
	if (highlight) {
	  match_text_color.g = 69;
	  match_text_color.b = 0;
	}

	this->font->render(this->renderer, text.c_str(),
	                   220, y, 1, match_text_color);
}

void MenuRenderer::renderMapOption(MapListItem& option, int y, bool highlight) {
	std::stringstream stream;
	stream << option.name;
	stream << " - Min: ";
	stream << option.minPlayers;
	stream << " - Max: ";
	stream << option.maxPlayers;
	std::string text = stream.str();

	SDL_Color text_color { 255, 255, 255 };
	if (highlight) {
	  text_color.g = 69;
	  text_color.b = 0;
	}

	this->font->render(this->renderer, text.c_str(),
										 250, y, 1, text_color);
}

void MenuRenderer::renderStatisticsScreen() {
  GameStatistics statistics = this->menu_status.getStatistics();

  YAML::Node node = this->config["statistics_box"];
  int box_x = node["x_pos"].as<int>();
  int box_y = node["x_pos"].as<int>();
  int box_w = node["width"].as<int>();
  int box_h = node["height"].as<int>();

  int gilding_w = node["gilding"].as<int>();

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
  SDL_RenderFillRect(this->renderer, &statistics_box);

  int back_text_x = node["back_text"]["x_pos"].as<int>();
  int back_text_y = node["back_text"]["y_pos"].as<int>();
  std::string back_text = node["back_text"]["text"].as<std::string>();

  SDL_Color back_text_color { 255, 69, 0 };

  this->font->render(this->renderer, back_text.c_str(), 
                     back_text_x, back_text_y, 
                     1, back_text_color);
}
