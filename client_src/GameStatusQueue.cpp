#include "GameStatusQueue.h"

GameStatusQueue::GameStatusQueue() : synchronized(false) { }

GameStatusQueue::~GameStatusQueue() { }

void GameStatusQueue::updateGameStatus(GameStatus new_game_status) {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (this->synchronized) this->cv.wait(lock);
	this->game_status = new_game_status; 
	/* Asignar el game status por copia puede ser poco eficiente. Capaz sea
	   más performante usar acá asignación por movimiento, o bien redefinir
	   la asignación por copia.
	   																	- Pablo (17/12/2020)						 */
	this->synchronized = true;
}

GameStatus& GameStatusQueue::getCurrentGameStatus() {
	std::unique_lock<std::mutex> lock(this->mutex);
	while (!this->synchronized) this->cv.wait(lock);
	this->synchronized = false;

	return this->game_status;
}