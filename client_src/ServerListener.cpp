#include <iostream>

#include "ServerListener.h"
#include "GameStatus.h"
#include "../common_src/Map.h"
#include "../common_src/Vector.h"

ServerListener::ServerListener(GameStatusMonitor& game_status_monitor)
: game_status_monitor(game_status_monitor) { }

ServerListener::~ServerListener() {
	this->join();
}

void ServerListener::run() {
	/* TODO: Acá se crea el GameStatus con toda la data inicial hardcodeada
		y se lo pasa al GameStatusMonitor como hack para poder inicializar el
		programa sin necesitar un socket.
			A futuro, para tener un menú inicial tendría que haber una clase
		intermedia que delegue el updateo del GameStatus a ServerListener o a
		un MenuHandler (o algo por el estilo) dependiendo de si se encuentra
		en el medio de una partida o no.
																	- Pablo (20/12/2020)								 */
	Map map("assets/maps/map.yml");
	GameStatusUpdate initial_state { Vector(1,1), 100, 0, 0, 0, true };

	this->game_status_monitor.initializeGameStatus(map, initial_state);

	while (true) {
		GameStatusUpdate update { Vector(1,1), 100, 0, 0, 0, true };
		this->game_status_monitor.updateGameStatus(update);
	}

	GameStatusUpdate shutdown_state { Vector(0,0), 0, 0, 0, 0, false };
	this->game_status_monitor.updateGameStatus(shutdown_state);
}
