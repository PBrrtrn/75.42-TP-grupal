#include "thread_game.h"

ThreadGame:: ThreadGame(int gameId,BlockingQueue<Message>* m) : 
id(gameId), messages(m),gameStatus("./maps/map-data.yml") {}

void ThreadGame:: run() {
	
	this->keep_running = true;
	
	std::cout << "Game started!" << std::endl;
    while (keep_running) {
        
        this->checkNews();
        this->checkPlayerPickups();
        this->respawnItems();
        this->checkPlayerBullets();
        this->sendGameUpdates();
        
        usleep(1000000/60); //todo: hacer variable respecto a tiempo demorado en ejecutar checkNews y sendUpdates
        
    }
    
    this->sendGameStatistics();
    
}

GameStatus ThreadGame:: getGameStatus() {
	return this->gameStatus;
}

void ThreadGame::respawnItems(){
	//iterar por todos los items y checkear si hay que "revivirlos"
}

void ThreadGame::checkPlayerBullets(){
	//iterar por todos los players y checkear si hay que hacerlos cambiar al cuchillo
	this->gameStatus.checkPlayerBullets();
}


void ThreadGame::checkPlayerPickups(){
	
	this->gameStatus.checkPlayerPickups();
	
	//for all items en game status
	//comparar distancia de item contra todos los jugadores
	//si la distancia es menor a un entero en la configuracion, entonces pick up
}

void ThreadGame::sendGameStatistics(){
	
}

void ThreadGame::checkNews(){
	
	Message m = this->messages->pop();
	std::cout << "en el game: " << (char)m.getType() << ", client:" << m.getClientId() << std::endl;
	
	switch (m.getType())
	{
	case TYPE_MOVE_FORWARD:
		this->tryMoveForward(m.getClientId());
		break;

	case TYPE_MOVE_BACKWARD:
		this->tryMoveBackward(m.getClientId());
		break;
	
	case TYPE_MOVE_LEFT:
		this->tryMoveLeft(m.getClientId());
		break;

	case TYPE_MOVE_RIGHT:
		this->tryMoveRight(m.getClientId());
		break;

	case TYPE_EXIT_GAME:
		this->expelClient(m.getClientId());
		break;
	
	case TYPE_SHOOT:
		this->tryShoot(m.getClientId());
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

void ThreadGame::sendGameUpdates(){
	for (auto& it: this->out_queues) {
        int clientId = it.first;
        
        this->out_queues.at(clientId)->push(this->gameStatus); 
        
        //int gameId = this->clientsInGames.at(it.first);
        //TODO: chequear tiempo de ejecucion -- eficiencia pasaje gamestatus
        //this->out_queues.at(clientId)->push(this->games.at(gameId)->getGameStatus());
    }
	
}

void ThreadGame::expelClient(int id){
	this->clients.erase(id);	
	if (this->clients.size() == 0)
		this->keep_running = false;
	//todo: keep_running = false si no hay mas clientes
}

void ThreadGame::addClient(ThreadClient* client, int id){
	
	std::cout << "en el game: " << this->id << ", client:" << id << " se inserto en este game." << std::endl;
	this->clients.insert({id,client});
	
	BlockingQueue<GameStatus>* queue_out = new BlockingQueue<GameStatus>();
    this->out_queues.insert(std::make_pair(id, queue_out));
    client->assignToOutQueue(queue_out);
	
	Vector position(3,4);
	Vector direction(1,0);
	this->gameStatus.addPlayer(id, position, direction);
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

ThreadGame:: ~ThreadGame(){}
