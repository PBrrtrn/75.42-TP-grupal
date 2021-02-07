#include <iostream>

#include "MenuStatusUpdater.h"

MenuStatusUpdater::MenuStatusUpdater(UpdateQueue& update_queue, 
																		 MenuStatus& menu_status,
																		 ServerConnection& server_connection,
																		 std::atomic<bool>& in_game)
: menu_status(menu_status), update_queue(update_queue),
	server_connection(server_connection), in_game(in_game) { }

MenuStatusUpdater::~MenuStatusUpdater() { }

void MenuStatusUpdater::updateStatus() {
	std::vector<GameOption> options = this->menu_status.getGameOptions();

	options.empty() ? refresh() : applyUpdate(options);
}

void MenuStatusUpdater::refresh() {
	std::vector<GameOption> options = this->server_connection.fetchGameOptions();

	this->menu_status.updateGameOptions(options);
}

void MenuStatusUpdater::applyUpdate(std::vector<GameOption>& options) {
	UpdateType update = this->update_queue.popUpdate();

	int selected_option = this->menu_status.getSelectedOption();

	if (update == MENU_SELECT_OPTION) {
		if (selected_option == 0) {
			refresh();
		} else if (selected_option == 1) {
			// Mostrar los mapas disponibles
		} else {
			// Pedir al server que te agregue a la partida
			this->in_game = true;
		}
	} else {
		int n_options = options.size() + 2;
		int move_direction = ((update == MENU_MOVE_UP) ? 1 : -1);
		int new_selection = (selected_option + move_direction) % n_options;
		if (new_selection < 0) new_selection = - new_selection;
		// Aca se rompe algo, revisar

		this->menu_status.updateSelectedOption(new_selection);
	}
}
