#include "MenuStatus.h"

MenuStatus::MenuStatus(std::atomic<bool>& in_game) 
: in_game(in_game), selected_option(0) { } 

MenuStatus::~MenuStatus() { }

std::vector<GameOption>& MenuStatus::getGameOptions() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->game_options;
}

int MenuStatus::getSelectedOption() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->selected_option;
}

void MenuStatus::updateGameOptions(std::vector<GameOption>& new_options) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->game_options = new_options;
}

void MenuStatus::updateSelectedOption(int new_selected_option) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->selected_option = new_selected_option;
}
