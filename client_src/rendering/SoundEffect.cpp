#include "SoundEffect.h"

SoundEffect::SoundEffect(const char* filepath) : sound_effect(NULL) {
	this->sound_effect = Mix_LoadWAV(filepath);
	if (this->sound_effect == NULL)
		throw "error loading sound effect";
		// throw SFXConstructorError(Mix_GetError());
}

SoundEffect::~SoundEffect() {
	Mix_FreeChunk(this->sound_effect);
}

void SoundEffect::play() {
	Mix_PlayChannel(-1, this->sound_effect, 0);
}
