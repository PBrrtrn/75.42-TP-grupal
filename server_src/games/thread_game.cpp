#include "thread_game.h"

ThreadGame:: ThreadGame(int gameId,BlockingQueue<Message>* m, 
	std::unordered_map<int,GameListItem>& list, std::string map_location, int mapId, 
	LobbyStatus& lobbyStatus) : 
	id(gameId), messages(m), gameStatus(map_location), gameList(list),
	map_id(mapId), lobbyStatus(lobbyStatus) {
		this->remaining_time = 30 * 1000; // Fijar por config
		this->waiting_time_to_start = 120; 
		this->start_running = true;
		this->is_dead = false;
}

void ThreadGame:: run() {
	std::cout << "Game " << std::to_string(this->id) << " waiting for more players!" << std::endl;
	
	GameListItem game;
	game.gameId = this->id;
	game.players = this->clients.size();
	game.maxPlayers = this->gameStatus.getMaxPlayers();
	game.mapId = this->map_id;
	
	this->gameList.insert({this->id,game});

	while(start_running) {
		if ( (this->gameStatus.getAlivePlayers() == this->gameStatus.getMaxPlayers()) || 
		 (this->gameStatus.getAlivePlayers() >= this->gameStatus.getMinPlayers() && this->waiting_time_to_start == 0)) {
			this->keep_running = true;
			this->start_running = false;
		} else if (this->gameStatus.getAlivePlayers() < this->gameStatus.getMinPlayers() && this->waiting_time_to_start == 0) {
			this->keep_running = false;
			this->start_running = false;
		}
		
		this->gameList.at(this->id).players = this->clients.size();
		
		if (!start_running)
			break;
		this->sendLobbyStatus();
		usleep(1000000);
		this->waiting_time_to_start--;
	}
	//el juego ya esta por arrancar (o hubo timeout sin gente), lo saco de la lista de disponibles
	this->gameList.erase(this->id);
	
	std::cout << "Game started!" << std::endl;
	this->sendLobbyStatus();
	
	std::cout << "Sending map to each client" << std::endl;
	for (auto& it: this->out_queues) {
        int clientId = it.first;
        this->sendMapToClient(clientId);
    }

	this->fillTimedEvents();	
	
    while (keep_running) {
		auto start_t = std::chrono::steady_clock::now();

		this->checkNews();
		this->updatePlayerPositions();
		this->updatePlayerRotations();
		this->updateShootingTime(1000000/29);
        this->checkPlayerPickups();
        this->respawnItems();
        this->checkPlayerBullets();
        this->sendGameUpdates();
        
		auto t = std::chrono::steady_clock::now() - start_t;
    	auto sleep_t = std::chrono::duration_cast<std::chrono::microseconds>(t);
    	usleep((1000000/29) - sleep_t.count());

        this->remaining_time--;
		this->keep_running = this->gameStatus.getAlivePlayers() > 1 && this->remaining_time != 0 && !this->is_dead;
    }
    
    this->sendGameStatistics();
	this->is_dead = true;
}

void ThreadGame::sendMapToClient(int clientId){
	this->out_queues.at(clientId)->push(Message(TYPE_SERVER_SEND_MAP, 0, clientId));
}

void ThreadGame::respawnItems(){
	this->gameStatus.respawnItems();
}

void ThreadGame::checkPlayerBullets(){
	this->gameStatus.checkPlayerBullets();
}

void ThreadGame::checkPlayerPickups(){
	this->gameStatus.checkPlayerPickups();
}

void ThreadGame::sendGameStatistics(){
	for (auto& it: this->out_queues) {
        int clientId = it.first;
        this->out_queues.at(clientId)->push(Message(TYPE_SERVER_SEND_GAME_STATISTICS, this->id, clientId));
    }
}

void ThreadGame::checkNews() {
	this->messages->lock();
	while (!this->messages->isEmptySync()) {
		Message m = this->messages->popSync();
		
		switch (m.getType())
		{
		case TYPE_MOVE_FORWARD_START:
			this->changeMovementState(m.getClientId(), STATE_MOVING_FORWARD);
			break;

		case TYPE_MOVE_BACKWARD_START:
			this->changeMovementState(m.getClientId(), STATE_MOVING_BACKWARDS);
			break;
		
		case TYPE_MOVE_LEFT_START:
			this->changeRotationState(m.getClientId(),STATE_MOVING_LEFT);
			break;

		case TYPE_MOVE_RIGHT_START:
			this->changeRotationState(m.getClientId(),STATE_MOVING_RIGHT);
			break;

		case TYPE_MOVE_FORWARD_STOP:
		case TYPE_MOVE_BACKWARD_STOP:
			this->changeMovementState(m.getClientId(), STATE_NOT_MOVING);
			break;
		case TYPE_MOVE_LEFT_STOP:
		case TYPE_MOVE_RIGHT_STOP:
			this->changeRotationState(m.getClientId(),STATE_NOT_MOVING);
			break;

		case TYPE_EXIT_GAME:
			this->expelClient(m.getClientId());
			break;
		
		case TYPE_SHOOT_STOP:
			std::cout << "en type shoot stop th game " << std::endl;
			this->changeShootingState(m.getClientId(), STATE_NOT_SHOOTING);
			break;

		case TYPE_SHOOT_START:
			//this->tryShoot(m.getClientId());
			std::cout << "en type shoot start th game " << std::endl;
			this->changeShootingState(m.getClientId(), STATE_SHOOTING);
			break;
		
		case TYPE_CHANGE_AMETRALLADORA:
			this->changeWeaponAmetralladora(m.getClientId());
			break;
		
		case TYPE_CHANGE_CANION:
			this->changeWeaponCanion(m.getClientId());
			break;

		case TYPE_CHANGE_CUCHILLO:
			this->changeWeaponCuchillo(m.getClientId());
			break;

		case TYPE_CHANGE_LANZA_COHETES:
			this->changeWeaponLanzacohetes(m.getClientId());
			break;

		case TYPE_CHANGE_PISTOLA:
			this->changeWeaponPistola(m.getClientId());
			break;
			
		case TYPE_USE_DOOR:
			this->useDoor(m.getClientId());
			break;		

		default:
			break;
		}
	}
	this->messages->unlock();
}

void ThreadGame::sendLobbyStatus() {
	this->lobbyStatus.updateLobbyData(this->id, this->waiting_time_to_start, this->clients.size(),
            this->getMaxPlayers(), !this->start_running);
	for (auto& it: this->out_queues) {
        int clientId = it.first;
        this->out_queues.at(clientId)->push(Message(TYPE_LOBBY_STATUS_UPDATE, this->id ,clientId)); 
    }
}

void ThreadGame::sendGameUpdates(){
	for (auto& it: this->clientGameStatuses) {
        int clientId = it.first;
        this->clientGameStatuses.at(clientId)->updateThisGameStatus();
    }	
	for (auto& it: this->out_queues) {
        int clientId = it.first;
        this->out_queues.at(clientId)->push(Message(TYPE_SERVER_SEND_GAME_UPDATE, 0, clientId));
    }
}

void ThreadGame::expelClient(int id){
	this->clients.erase(id);	
	if (this->clients.size() <= 1){
		this->shutdown();
	}
}

bool ThreadGame::addClient(ThreadClient* client, int id){
	if (!this->start_running) return false; //si el juego esta iniciado, no se pueden agregar
									//mas jugadores a la partida
	this->clients.insert({id,client});
	
	BlockingQueue<Message>* queue_out = new BlockingQueue<Message>();
    this->out_queues.insert(std::make_pair(id, queue_out));
    client->assignToOutQueue(queue_out);
    
	std::vector<SpawnPoint> spawnpoints = this->gameStatus.getSpawnPoints();
	int sp_idx = rand()% (spawnpoints.size());
	Vector position = spawnpoints.at(sp_idx).getPosition();
	Vector direction = spawnpoints.at(sp_idx).getDirection();
	this->gameStatus.addPlayer(id, position, direction);
	this->clientGameStatuses.insert({id, new ClientGameStatus(this->gameStatus,id)});
	client->assignToGameStatus(this->clientGameStatuses.at(id));
	return true;
}

void ThreadGame::changeMovementState(int playerId, MovementState state) {
	this->gameStatus.changeMovementState(playerId,state);
}

void ThreadGame::changeRotationState(int playerId,MovementState state) {
	this->gameStatus.changeRotationState(playerId,state);
}

void ThreadGame::changeShootingState(int playerId, ShootingState state) {
	std::cout << "en change shooting state" <<std::endl;
	this->gameStatus.changeShootingState(playerId, state);
	switch (state)
	{
	case STATE_NOT_SHOOTING:
		std::cout << "shoot deactivate en th game" <<std::endl;
		this->shooting_events.at(playerId)->deactivate();
		break;

	case STATE_SHOOTING:
		std::cout << "shoot activate en th game" <<std::endl;
		std::cout << "shoot activate a player id: " << playerId << std::endl;
		this->shooting_events.at(playerId)->activate(this->gameStatus.getShootTimeout(playerId));
		break;
	
	default:
		break;
	}
}

void ThreadGame::tryMoveForward(int id) {
    this->move_forward.tryAction(this->gameStatus, id);
}

void ThreadGame::tryMoveBackward(int id) {
    this->move_backward.tryAction(this->gameStatus, id);
}

void ThreadGame::tryMoveLeft(int id) {
    this->move_left.tryAction(this->gameStatus, id);
}

void ThreadGame::tryMoveRight(int id) {
    this->move_right.tryAction(this->gameStatus, id);
}

void ThreadGame::tryShoot(int id) {
	this->shoot.tryAction(this->gameStatus, id);
}

void ThreadGame::changeWeaponAmetralladora(int id){
	this->change_ametralladora.tryAction(this->gameStatus, id);
}

void ThreadGame::changeWeaponCanion(int id){
	this->change_canion.tryAction(this->gameStatus, id);
}

void ThreadGame::changeWeaponCuchillo(int id){
	this->change_cuchillo.tryAction(this->gameStatus,id);
}
void ThreadGame::changeWeaponLanzacohetes(int id){
	this->change_lanzacohetes.tryAction(this->gameStatus, id);
}

void ThreadGame::changeWeaponPistola(int id){
	this->change_pistola.tryAction(this->gameStatus, id);
}

void ThreadGame::useDoor(int id){
	this->use_door.tryAction(this->gameStatus,id);
}

char ThreadGame::getCurrentPlayers(){
	return this->clients.size();
}
char ThreadGame::getMaxPlayers(){
	return this->gameStatus.getMaxPlayers();
}

void ThreadGame::updatePlayerPositions(){
	std::unordered_map<int, MovementState> states = this->gameStatus.getPlayerMovementStates();
	for (auto s: states) {
		
		switch (s.second) {
			case STATE_MOVING_FORWARD:
				this->tryMoveForward(s.first);
				break;
			case STATE_MOVING_BACKWARDS:
				this->tryMoveBackward(s.first);
				break;
			default:
				break;	
		}
	}	
}

void ThreadGame::updatePlayerRotations(){
	std::unordered_map<int, MovementState> states = this->gameStatus.getPlayerRotationStates();
	for (auto s: states) {
		switch (s.second) {
			case STATE_MOVING_LEFT:
				this->tryMoveLeft(s.first);
				break;
			case STATE_MOVING_RIGHT:
				this->tryMoveRight(s.first);
				break;					
			default:
				break;	
		}
	}	
}

void ThreadGame::fillTimedEvents() {
	for (auto c: this->clients) {
		this->shooting_events.insert(std::make_pair(
			c.first, 
			new TimedEvent(&shoot, &Shoot::tryAction, c.first, this->gameStatus)
		));
	}
	std::cout << "---------TIMED EVENTS-----" << std::endl;
	for (auto c: this->shooting_events) {
		std::cout << "client id: " << c.first << "te: " << c.second << std::endl;
	}
	std::cout << "--------------------------" << std::endl;
}

void ThreadGame::updateShootingTime(float delta){
	//std::cout << "en update shooting time" << std::endl;
	for (auto te: this->shooting_events) {
		te.second->update(delta);
	}	
}

bool ThreadGame:: isDead() {
	return this->is_dead;
}

void ThreadGame::shutdown(){
	this->keep_running = false;
	this->start_running = false;
	this->is_dead = true;
}

ThreadGame:: ~ThreadGame(){
	for (auto x: this->out_queues) {
        delete x.second;
    }
}
