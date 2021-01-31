#ifndef __MENU_STATUS_H__
#define __MENU_STATUS_H__

#include <atomic>
#include <string>
#include <vector>
#include <mutex>

struct GameOption {
	std::string map_name;
	int max_players;
	int current_players;
	std::mutex mutex;
};

class MenuStatus {
private:
	std::mutex mutex;
	std::vector<GameOption> game_options;
	int selected_option;
	std::atomic<bool>& in_game;
public:
	MenuStatus(std::atomic<bool>& in_game);
	~MenuStatus();
	std::vector<GameOption>& getGameOptions();
	int getSelectedOption();
	void updateGameOptions(std::vector<GameOption>& new_options);
	void updateSelectedOption(int new_selected_option);
};

#endif