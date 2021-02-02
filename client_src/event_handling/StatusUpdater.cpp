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
				// Fetch options, actualizar menu_status
			} else {
				int selected_option = this->menu_status.getSelectedOption();

				if (update == MENU_SELECT_OPTION) {
					if (selected_option = 0) {
						// Fetch options, actualizar menu_status
					} else {
						// Pedir al server que te agregue a la partida
						in_game = true;
					}
				} else if (update != MENU_NONE) {
					int n_options = options.size() + 1;
					int move_direction = ((update == MENU_MOVE_UP) ? 1 : -1);
					int new_selection = (selected_option + move_direction) % n_options;

					this->menu_status.updateSelectedOption(new_selection);
				}
			}
		}
	}
}