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
		programa sin necesitar un socket. La idea sería que toda esta data se
		reciba por socket.
																	- Pablo (20/12/2020)								 */
	Map map("assets/maps/map.yml");
	GameStatusUpdate initial_state { Vector(1,1), 100, 0, 0 };
	this->game_status_monitor.initializeGameStatus(map, initial_state);
	while (true) {
		// Updatear GameStatus
	}
}
