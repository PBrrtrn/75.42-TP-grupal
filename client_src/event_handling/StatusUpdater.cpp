#include <iostream>
#include "StatusUpdater.h"

#include "../enums/UpdateType.h"

StatusUpdater::StatusUpdater(std::atomic<bool>& in_game,
														 UpdateQueue& update_queue,
														 MenuStatus& menu_status,
														 GameStatusMonitor& game_status_monitor)
: in_game(in_game), update_queue(update_queue), 
	menu_status(menu_status), game_status_monitor(game_status_monitor) { }

StatusUpdater::~StatusUpdater() { }

void StatusUpdater::run() {
	while (true) {
		if (this->in_game) {
			// Recibir un update del server por socket y actualizar GameStatus
		} else {
			UpdateType update = this->update_queue.popUpdate();
			/* POSIBLE MEJORA: Hacer que UpdateType sea una clase 
			que generalice los tipos de update, y que cada update
			se sepa aplicar a sí mismo al MenuStatus.	 				 */

			std::vector<GameOption> options = this->menu_status.getGameOptions();

			if (options.empty()) {
				// Hacer fetch de las opciones y actualizar el menu_status
				GameOption game_option { std::string("Mapin el mapa"), 4, 1 };
				options.push_back(game_option);

				this->menu_status.updateGameOptions(options);
			} else {
				int selected_option = this->menu_status.getSelectedOption();

				if (update == MENU_SELECT_OPTION) {
					if (selected_option == 0) {
						// Fetch options, actualizar menu_status
					} else if (selected_option == 1) {
						// Mostrar los mapas disponibles
					} else {
						// Pedir al server que te agregue a la partida
						in_game = true;
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
		}
	}
}