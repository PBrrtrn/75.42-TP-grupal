#ifndef __SOUND_EFFECT_H__
#define __SOUND_EFFECT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SoundEffect {
private:
	Mix_Chunk* sound_effect;
public:
	SoundEffect(const char* filepath);
	~SoundEffect();
	void play();
};

#endif