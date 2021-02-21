#ifndef __UPDATE_RECEIVER_H__
#define __UPDATE_RECEIVER_H__

#include <atomic>

#include "../../common_src/Thread.h"

#include "../ServerConnection.h"
#include "../game_status/GameStatusMonitor.h"
#include "../game_status/MenuStatus.h"
#include "../../common_src/MessageType.h"

class UpdateReceiver : public Thread {
private:
	std::atomic<bool>& in_game;
	ServerConnection& connection;
	GameStatusMonitor& game_status_monitor;
	MenuStatus& menu_status;
	void receiveGameUpdate(MessageType message_type);
	void receiveMenuUpdate(MessageType message_type);
	void fetchMap();
	void fetchGameUpdate();
	void fetchStatistics();
	void fetchMapOptions();
	void fetchGameOptions();
	void fetchLobbyStatus();
public:
	UpdateReceiver(std::atomic<bool>& in_game, 
								 ServerConnection& connection,
								 GameStatusMonitor& game_status_monitor,
								 MenuStatus& menu_status);
	~UpdateReceiver();
	void run();
};

#endif
