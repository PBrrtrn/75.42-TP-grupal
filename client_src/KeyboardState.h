#ifndef __KEYBOARD_STATE_H__
#define __KEYBOARD_STATE_H__

#include <unordered_map>
#include <SDL2/SDL.h>

enum KeyState { UP, DOWN };

class KeyboardState {
private:
	std::unordered_map<int, bool> keyboard_state;
public:
	KeyboardState();
	~KeyboardState();
	void toggleKeyDown(int key);
	void toggleKeyUp(int key);
	bool isDown(int key);
};

#endif