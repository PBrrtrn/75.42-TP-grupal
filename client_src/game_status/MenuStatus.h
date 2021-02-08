#ifndef __MENU_STATUS_H__
#define __MENU_STATUS_H__

#include <string>
#include <vector>
#include <mutex>

#include "../../common_src/GameListItem.h"

/*
struct GameOption {
	std::string map_name;
	int max_players;
	int current_players;
};
*/

class MenuStatus {
private:
	std::mutex mutex;
	std::vector<GameListItem> game_options;
	int selected_option;
public:
	MenuStatus();
	~MenuStatus();
	std::vector<GameListItem> getGameOptions();
	int getSelectedOption();
	void updateGameOptions(std::vector<GameListItem>& new_options);
	void updateSelectedOption(int new_selected_option);
};

#endif