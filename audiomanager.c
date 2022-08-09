#include "audiomanager.h"

/* Externals */
extern SDL_Rect playDest;
extern SDL_Rect forwardDest;
extern int isKeyDown(SDL_Scancode key);
extern void throw_Error(const char* title, const char* errmsg);

/* Internals */
static SDL_Point mousepointer;

int music_state = 1;

static void setup_audio_device() {
    if (!Mix_Init(MIX_INIT_MP3)) { // returns 0 on failure
        throw_Error("Mixer Failed", Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)) {
        throw_Error("Device Failed", Mix_GetError());
    }
	SDL_Log("Audio Device opened");
	
}

void InitAudioDevice() { setup_audio_device(); }

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

void Forward(int byKey) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &forwardDest) || byKey) {
		SDL_Log("moving forward\n");
		next_music();
	}
}

void DeinitAudioDevice() {
	Mix_CloseAudio();
	Mix_Quit();
}
