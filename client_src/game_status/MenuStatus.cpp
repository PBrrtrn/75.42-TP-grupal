#include "MenuStatus.h"

MenuStatus::MenuStatus() : selected_option(0) { }

MenuStatus::~MenuStatus() { }

std::vector<GameListItem> MenuStatus::getGameOptions() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->game_options;
}

int MenuStatus::getSelectedOption() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->selected_option;
}

void MenuStatus::updateGameOptions(std::vector<GameListItem>& new_options) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->game_options = new_options;
}

void MenuStatus::updateSelectedOption(int new_selected_option) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->selected_option = new_selected_option;
}
