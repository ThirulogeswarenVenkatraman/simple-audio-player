#include "audiomanager.h"

extern SDL_Rect playDest;
extern SDL_Rect stopDest;
extern int isKeyDown(SDL_Scancode key);
extern void throw_Error(const char* title, const char* errmsg);

int music_state = 1;

void PlayMusic(Mix_Music* _music, int times) {
	if (Mix_PlayMusic(_music, times)) {
		throw_Error("Error Playing", Mix_GetError());
	}
}

static SDL_Point mousepointer;
void PlaynPause(int byKey) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &playDest) || byKey) {
		if (!music_state) {
			SDL_Log("Resumed\n");
			Mix_ResumeMusic();
			music_state = 1;
		}
		else {
			SDL_Log("Paused\n");
			Mix_PauseMusic();
			music_state = 0;
		}
	}
}

void Stop(int byKey) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &stopDest) || byKey) {
		if (music_state) {
			SDL_Log("Stopped\n");
			Mix_PauseMusic();
			music_state = 0;
		}
	}
}