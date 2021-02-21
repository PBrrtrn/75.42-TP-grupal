#include "game_manager.h"

GameManager::GameManager() : serverStatus(this->games_list, this->mapsRepo){
	this->clients_counter = 0;
    this->games_counter = 0;
}


void GameManager:: newMessage(Message message) {
    this->_parse_message(message);
}

void GameManager:: _parse_message(Message message){}

void GameManager::receiveMessages() {
    //std::vector<Message> messages = this->lobby_messages.popAll();

	//for (std::vector<Message>::iterator it = messages.begin() ; it != messages.end(); ++it) {
        Message m = this->lobby_messages.pop();
        switch (m.getType())
        {
        case CLIENT_REQUEST_CREATE_GAME:
            this->startGame(m.getClientId(), m.getEntity());
            break;
        
        case CLIENT_REQUEST_JOIN_GAME:
            this->joinGame(m.getClientId(), m.getEntity());
            break;

        case CLIENT_REQUEST_GAMES_LIST:
            this->informAvailableGames(m.getClientId());
            break;
        case CLIENT_REQUEST_MAPS_LIST:
            this->sendMapsList(m.getClientId());
            break;
        case CLIENT_REQUEST_LEAVE_GAME:
            this->expelClient(m.getClientId());
            break;        
        case TYPE_CLIENT_PING:
            break;     
        
        /*si el cliente mando un mensaje que esta asociado al juego donde 
        * esta jugando*/
        default:
            //int gameId = this->clientsInGames.at(m.getClientId());
            //this->queues.at(gameId)->push(m.;
            break;
        }
    }
//}

void GameManager::expelClient(int expelledClientId){
	if (this->clientsInGames.find(expelledClientId) != this->clientsInGames.end()) {
		this->games.at(this->clientsInGames.at(expelledClientId))->expelClient(expelledClientId);
	} else {
		this->clientsThreads.at(expelledClientId)->shutdown();
		this->clientsThreads.erase(expelledClientId);
	}
	
}

void GameManager::startGame(int clientIdStarter, int mapId) {
    if (this->mapsRepo.validMap(mapId)) {
        ProtectedQueue<Message>* receiver = new ProtectedQueue<Message>();
        std::cout << "map location:" << this->mapsRepo.getMapLocation(mapId) << std::endl;
        this->games.insert({ 
                            this->games_counter, 
                            new ThreadGame(this->games_counter,
                                            receiver,
                                            this->games_list, 
                                            this->mapsRepo.getMapLocation(mapId),
                                            mapId, this->lobbyStatus) 
                            });
        this->clientsInGames.insert({clientIdStarter,this->games_counter});
        this->messageReceiver.insert(std::make_pair(this->games_counter, receiver));
        this->joinGame(clientIdStarter, this->games_counter);
        this->games.at(this->games_counter)->start();
        this->games_counter++;
    } else {
        //TODO enviar al cliente diciendole que no pudo iniciar el juego
        //refused por map id invalido
    }
}

void GameManager::joinGame(int clientId, int gameId) {
	//Si el juego EXISTE y logra realizar addClient
    if (this->games.find(gameId) != this->games.end() && 
	 this->games.at(gameId)->addClient(this->clientsThreads.at(clientId), clientId)) {
		this->clientsInGames.insert({clientId, gameId});
        std::cout << "cambiando cola" << std::endl;
        this->clientMessageReceiver.at(clientId)->assignToGameQueue(this->messageReceiver.at(gameId));
        this->out_queues.at(clientId)->push(Message(TYPE_SERVER_JOIN_OK, 0, clientId));
	} else {
        this->out_queues.at(clientId)->push(Message(TYPE_SERVER_JOIN_REFUSED, 0, clientId));
    }
}

void GameManager::acceptClient(Socket&& socket){
	std::cout << "Game manager accepted new Client. ClientId:"<< this->clients_counter << std::endl;
	
	int clientId = this->clients_counter;
	this->out_queues.insert({clientId, new BlockingQueue<Message>()} );

    this->clientMessageReceiver.insert({clientId, new ReceiveClientMessages(std::move(socket), &this->lobby_messages)});
    this->clientMessageReceiver.at(clientId)->start();

    this->clientsThreads.insert({clientId, 
        new ThreadClient(clientId, this->out_queues.at(clientId), 
        this->clientMessageReceiver.at(clientId)->getPeerReference(), 
        this->serverStatus, this->lobbyStatus)});
    
    this->clientsThreads.at(clientId)->start();

    this->clients_counter++;
}

void GameManager::informAvailableGames(int clientId){
	this->out_queues.at(clientId)->push(Message(TYPE_SERVER_SEND_GAMES_LIST, 0, clientId));
}

void GameManager::sendMapsList(int clientId) {
    this->out_queues.at(clientId)->push(Message(TYPE_SERVER_SEND_MAP_LIST, 0, clientId));
}

void GameManager::cleanUpDeadGames(){
	for (auto x: this->games) {
        if (x.second->isDead()) {
            x.second->join();
            delete x.second;
            this->games.erase(x.first);
        }
    }
}

GameManager::~GameManager(){
    for (auto x: this->clientsThreads) {
        x.second->shutdown();
        x.second->join();
        delete x.second;
    }
    for (auto x: this->games) {
        x.second->shutdown();
        x.second->join();
        delete x.second;
    }
    /*
    for (auto x: this->queues) {
        delete x.second;
    }*/
    for (auto x: this->out_queues) {
        delete x.second;
    }
}
