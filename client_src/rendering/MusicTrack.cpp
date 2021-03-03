#include <iostream>

#include "MusicTrack.h"

MusicTrack::MusicTrack(const char* filepath) : music_track(NULL) {
	this->music_track = Mix_LoadMUS(filepath);
	if (this->music_track == NULL)
		throw "error loading music track";
		// throw TrackConstructorError(Mix_GetError());
}

MusicTrack::~MusicTrack() {
	Mix_FreeMusic(this->music_track);
}

void MusicTrack::play() {
	Mix_PlayMusic(this->music_track, -1);
}

void MusicTrack::pause() {
	Mix_PauseMusic();
}
/*
TrackConstructorError::TrackConstructorError
                (const char *error) noexcept {
  snprintf(this->error_msg, ERROR_BUF_LEN, 
           "Failed to build music track: %s", error);
}

TrackConstructorError::~TrackConstructorError() noexcept { }

const char* TrackConstructorError::what() const noexcept {
  return this->error_msg;
}
*/