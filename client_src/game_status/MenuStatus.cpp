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

LobbyStatusData MenuStatus::getLobbyStatus() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->lobby_status;
}

GameStatistics MenuStatus::getStatistics() {
	std::unique_lock<std::mutex> lock(this->mutex);
	return this->statistics;
}

void MenuStatus::updateGameOptions(std::vector<GameListItem>& new_options) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->game_options = new_options;
}

void MenuStatus::updateMapOptions(std::vector<MapListItem>& new_options) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->map_options = new_options;
}

void MenuStatus::updateLobbyStatus(LobbyStatusData new_lobby_status) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->lobby_status = new_lobby_status;
}

void MenuStatus::updateCurrentScreen(Screen new_screen) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->current_screen = new_screen;
}

void MenuStatus::updateStatistics(GameStatistics new_statistics) {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->statistics = new_statistics;
}

void MenuStatus::selectOptionUp() {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->moveSelectedOption(1);
}

void MenuStatus::selectOptionDown() {
	std::unique_lock<std::mutex> lock(this->mutex);
	this->moveSelectedOption(-1);
}

void MenuStatus::moveSelectedOption(int direction) {
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
