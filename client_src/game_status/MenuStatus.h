#ifndef __MENU_STATUS_H__
#define __MENU_STATUS_H__

#include <string>
#include <vector>
#include <mutex>

#include "../../common_src/GameListItem.h"
#include "../../common_src/MapListItem.h"
#include "../../common_src/ClientGameStatusElements.h"
#include "../../common_src/LobbyStatusData.h"

enum Screen { GAME_SELECTION, LOBBY, GAME_CREATION, STATISTICS };

class MenuStatus {
private:
	std::mutex mutex;
	std::vector<GameListItem> game_options;
	std::vector<MapListItem> map_options;
	LobbyStatusData lobby_status;
	GameStatistics statistics;
	Screen current_screen;
	int selected_option;
	void moveSelectedOption(int direction);
public:
	MenuStatus();
	~MenuStatus();
	std::vector<GameListItem> getGameOptions();
	std::vector<MapListItem> getMapOptions();
	Screen getCurrentScreen();
	int getSelectedOption();
	LobbyStatusData getLobbyStatus();
	GameStatistics getStatistics();
	void updateGameOptions(std::vector<GameListItem>& new_options);
	void updateMapOptions(std::vector<MapListItem>& new_options);
	void updateLobbyStatus(LobbyStatusData new_lobby_status);
	void updateCurrentScreen(Screen new_screen);
	void updateStatistics(GameStatistics new_statistics);
	void selectOptionUp();
	void selectOptionDown();
};

#endif