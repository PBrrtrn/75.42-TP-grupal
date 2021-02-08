#ifndef __MENU_STATUS_UPDATER_H__
#define __MENU_STATUS_UPDATER_H__

#include <vector>
#include <atomic>

#include "UpdateQueue.h"
#include "../game_status/MenuStatus.h"
#include "../ServerConnection.h"
#include "../enums/UpdateType.h"
#include "../../common_src/GameListItem.h"
#include "../../common_src/MapListItem.h"

class MenuStatusUpdater {
private:
	UpdateQueue& update_queue;
	MenuStatus& menu_status;
	ServerConnection& server_connection;
	std::atomic<bool>& in_game;
	void refresh();
	void handleStartGameScreen(int selected_option, UpdateType update);
	void handleLobbyScreen(int selected_option, UpdateType update);
public:
	MenuStatusUpdater(UpdateQueue& update_queue, 
										MenuStatus& menu_status,
										ServerConnection& server_connection,
										std::atomic<bool>& in_game);
	~MenuStatusUpdater();
	void updateStatus();
};

#endif