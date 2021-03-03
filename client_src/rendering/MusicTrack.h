#ifndef __MUSIC_TRACK_H__
#define __MUSIC_TRACK_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MusicTrack {
private:
	Mix_Music* music_track;
public:
	MusicTrack();
	~MusicTrack();
};

#endif
