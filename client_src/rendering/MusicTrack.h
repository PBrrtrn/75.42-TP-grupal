#ifndef __MUSIC_TRACK_H__
#define __MUSIC_TRACK_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MusicTrack {
private:
	Mix_Music* music_track;
public:
	MusicTrack(const char* filepath);
	~MusicTrack();
	void play();
	void pause();
};

#define ERROR_BUF_LEN 256

class TrackConstructorError : public std::exception {
private:
  char error_msg[ERROR_BUF_LEN];
public:
  explicit TrackConstructorError(const char* mix_error) noexcept;
  virtual const char* what() const noexcept;
  virtual ~TrackConstructorError() noexcept;
};

#endif