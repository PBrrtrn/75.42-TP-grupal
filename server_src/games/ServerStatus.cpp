#include "ServerStatus.h"

ServerStatus::ServerStatus(std::unordered_map<int, 
	GameListItem>& games, MapRepository& mapRepository) : 
	games(games), mapRepo(mapRepository){}

std::vector<GameListItem> ServerStatus::getGamesList() {
	
	//int size = this->games.size();
	//reservo de antemano toda la memoria que necesito para los items
	//std::vector<GameListItem> list(size); //TODO ARREGLAR BUG DUPLICA LOS ELEMENTOS

	std::vector<GameListItem> list;
	GameListItem game;
	
	for (auto& it: this->games) {
		list.emplace_back(it.second);
	}

	return std::move(list);

}	

std::vector<MapListItem> ServerStatus::getMapsList() {
	return this->mapRepo.getMapVector();
}

ServerStatus::~ServerStatus(){ }
