#include "UIDrawer.h"

UIDrawer::UIDrawer(SDL_Renderer* renderer, YAML::Node config) {
	this->load(renderer, config);

	this->ui_bar_dimensions.x = config["bar"]["x_pos"].as<int>();
	this->ui_bar_dimensions.y = config["bar"]["y_pos"].as<int>();
	this->ui_bar_dimensions.w = config["bar"]["width"].as<int>();
	this->ui_bar_dimensions.h = config["bar"]["height"].as<int>();

	this->key_icon_dimensions.x = config["key_icon"]["x_pos"].as<int>();
	this->key_icon_dimensions.y = config["key_icon"]["y_pos"].as<int>();
	this->key_icon_dimensions.w = config["key_icon"]["width"].as<int>();
	this->key_icon_dimensions.h = config["key_icon"]["height"].as<int>();
}

UIDrawer::~UIDrawer() {
	delete this->font;
	delete this->key_icon_texture;
	delete this->ui_bar_texture;
}

void UIDrawer::load(SDL_Renderer* renderer, YAML::Node config) {
	std::string path = config["directory"].as<std::string>();

	std::string key_icon_file = config["key_icon"]["texture"].as<std::string>();
	std::string key_texture_filepath = path + key_icon_file;
	this->key_icon_texture = new Texture(renderer, key_texture_filepath.c_str());

	std::string bar_texture_file = config["bar"]["texture"].as<std::string>();
	std::string bar_texture_filepath = path + bar_texture_file;
	this->ui_bar_texture = new Texture(renderer, bar_texture_filepath.c_str());

	std::string font_file = config["font"].as<std::string>();
	std::string font_filepath = path + font_file;
	this->font = new Font(font_filepath);
}

void UIDrawer::draw(SDL_Renderer* renderer, uint8_t health, 
										uint8_t enemies_alive, uint8_t ammo, 
										uint8_t lives, bool has_key) {
	this->ui_bar_texture->render(renderer, NULL, &(this->ui_bar_dimensions));

	SDL_Color text_color { 158, 158, 255 };

	this->font->render(renderer, std::to_string(enemies_alive).c_str(),
										 35, 450, 1, text_color);

	this->font->render(renderer, "0", // Reemplazar por el score del jugador
										 130, 450, 1, text_color);

	this->font->render(renderer, std::to_string(lives).c_str(),
										 230, 450, 1, text_color);

	this->font->render(renderer, std::to_string(health).c_str(),
										 375, 450, 1, text_color);

	this->font->render(renderer, std::to_string(ammo).c_str(),
										 450, 450, 1, text_color);
}