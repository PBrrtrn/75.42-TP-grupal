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

void MenuStatus::updateCurrentScreen(Screen new_screen) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->current_screen = new_screen;
}

void MenuStatus::selectOptionUp() {
	std::unique_lock<std::mutex> lock(this->mutex);

	this->moveSelectedOption(1);
}

void MenuStatus::selectOptionDown() {
	std::unique_lock<std::mutex> lock(this->mutex);

	this->moveSelectedOption(-1);
}

void moveSelectedOption(int direction) {
	int n_options;
	if (this->current_screen == GAME_SELECTION)
		n_options = this->game_options.size() + 2;
	else if (this->current_screen = GAME_CREATION)
		n_options = this->map_options.size() + 1;
	else
		n_options = 1;

	int new_selection = (this->selected_option + direction) % n_options;
	if (new_selection < 0) new_selection = - new_selection;
	this->selected_option = new_selection;
}
