#include "lobbyStatus.h"

LobbyStatus::LobbyStatus(){}

void LobbyStatus::updateLobbyData(int gameID, int remainingTime, int players,
    int maxPlayers, bool gameStarted) {
    LobbyStatusData lobbyStatus;
    lobbyStatus.remainingTime = remainingTime;
    lobbyStatus.players = players;
    lobbyStatus.maxPlayers = maxPlayers;
    lobbyStatus.gameStarted = gameStarted;
    
    if (this->lobbysData.find(gameID) == this->lobbysData.end()) {
        this->lobbysData.insert({gameID, lobbyStatus});
    } else {   
        this->lobbysData.at(gameID) = lobbyStatus;
    }
}

LobbyStatusData LobbyStatus::getLobbyStatus(int gameID) {
    return this->lobbysData.at(gameID);
}
        
LobbyStatus::~LobbyStatus(){}
