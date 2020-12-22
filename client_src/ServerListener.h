#ifndef __SERVER_LISTENER_H__
#define __SERVER_LISTENER_H__

#include "Thread.h"
#include "GameStatusMonitor.h"

class ServerListener : public Thread {
private:
	GameStatusMonitor& game_status_monitor;
public:
	ServerListener(GameStatusMonitor& game_status_monitor);
	~ServerListener();
	void run();
};

#endif