#include "ServerStatus.h"

ServerStatus::ServerStatus(std::unordered_map<int, 
	GameListItem>& games, MapRepository& mapRepository) : 
	games(games), mapRepo(mapRepository){}

std::vector<GameListItem> ServerStatus::getGamesList() {
	std::vector<GameListItem> list;
	GameListItem game;
	
	for (auto& it: this->games) {
		list.emplace_back(it.second);
	}

	return std::move(list);
}	

const std::vector<MapListItem>& ServerStatus::getMapsList() {
	return this->mapRepo.getMapVector();
}

ServerStatus::~ServerStatus(){ }
