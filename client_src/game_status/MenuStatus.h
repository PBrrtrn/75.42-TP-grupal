#ifndef __MENU_STATUS_H__
#define __MENU_STATUS_H__

#include <string>
#include <vector>
#include <mutex>

#include "../../common_src/GameListItem.h"
#include "../../common_src/MapListItem.h"

enum Screen { GAME_SELECTION, LOBBY, GAME_CREATION };

class MenuStatus {
private:
	std::mutex mutex;
	std::vector<GameListItem> game_options;
	std::vector<MapListItem> map_options;
	Screen current_screen;
	int selected_option;
public:
	MenuStatus();
	~MenuStatus();
	std::vector<GameListItem> getGameOptions();
	std::vector<MapListItem> getMapOptions();
	Screen getCurrentScreen();
	int getSelectedOption();
	void updateGameOptions(std::vector<GameListItem>& new_options);
	void updateMapOptions(std::vector<MapListItem>& new_options);
	void updateSelectedOption(int new_selected_option);
	void updateCurrentScreen(Screen new_screen);
};

#endif