#include "ServerStatus.h"

ServerStatus::ServerStatus(std::unordered_map<int, GameListItem>& games) : games(games){ }

char ServerStatus::getGameListSize(){
	
	//char listSize = 0;

	
	//return this->games.size();
	
	return 0;
	
}

std::vector<GameListItem> ServerStatus::getGamesList() {
	
	int size = this->games.size();
	
	//reservo de antemano toda la memoria que necesito para los items
	//std::vector<GameListItem> list(size); //TODO ARREGLAR BUG DUPLICA LOS ELEMENTOS
	std::vector<GameListItem> list;
	GameListItem game;
	
	for (auto& it: this->games) {
		list.emplace_back(it.second);
	}

	return std::move(list);

}	


void getGameListItem(char id,GameListItem& game){
	//ThreadGame* gameThread;
	//try{
	//	gameThread = this->games.at(id);
	//} catch (...) {
	//	return false;
	//}
	//if ()
	//game.gameId = id;
	//game.players = gameThread->
	
	/*	char gameId;
	char players;
	char maxPlayers;
	char mapId;*/
	
	
}

ServerStatus::~ServerStatus(){ }
