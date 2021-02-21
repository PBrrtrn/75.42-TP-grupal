#include "MenuStatus.h"

MenuStatus::MenuStatus() : selected_option(0), current_screen(GAME_SELECTION) { }

MenuStatus::~MenuStatus() { }

std::vector<GameListItem> MenuStatus::getGameOptions() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->game_options;
}

std::vector<MapListItem> MenuStatus::getMapOptions() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->map_options;
}

Screen MenuStatus::getCurrentScreen() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->current_screen;
}

int MenuStatus::getSelectedOption() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->selected_option;
}

void MenuStatus::updateGameOptions(std::vector<GameListItem>& new_options) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->game_options = new_options;
}

void MenuStatus::updateMapOptions(std::vector<MapListItem>& new_options) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->map_options = new_options;
}

void MenuStatus::updateSelectedOption(int new_selected_option) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->selected_option = new_selected_option;
}

void MenuStatus::updateCurrentScreen(Screen new_screen) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->current_screen = new_screen;
}

