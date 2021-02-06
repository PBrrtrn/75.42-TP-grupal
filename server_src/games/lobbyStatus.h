#ifndef __LOBBY_STATUS_H_
#define __LOBBY_STATUS_H_

#include "../../common_src/LobbyStatusData.h"
#include <unordered_map>

class LobbyStatus {
    private:
        /*key: game id, value: lobby status data*/
        std::unordered_map<int, LobbyStatusData> lobbysData;
    public:
        LobbyStatus();

        void updateLobbyData(int gameID, int remainingTime, int players,
            int maxPlayers, bool gameStarted);

        LobbyStatusData getLobbyStatus(int gameID);
        
        ~LobbyStatus();
};

#endif
