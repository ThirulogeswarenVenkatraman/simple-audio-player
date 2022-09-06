#include "include/audiomanager.h"

/* Externals */
extern SDL_Rect playDest;
extern SDL_Rect cqDest;
extern void throw_error(const char* title, const char* errmsg);

/* Internals */
static SDL_Point mousepointer;

/* 1 -> Playing */
int music_state = 1;

static void setup_audio_device() {
    if (!Mix_Init(MIX_INIT_MP3)) { // returns 0 on failure
		throw_error("Mixer Failed", Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)) {
		throw_error("Device Failed", Mix_GetError());
    }
	SDL_Log("Audio Device opened");
	
}

void InitAudioDevice() {
	setup_audio_device();
}

void current_play_n_pause(int byKey) {
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

void clear_audio_queue() { 
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &cqDest)) {
		FreeAudioQueue();
		SDL_Log("freed");
	}
}

void DeinitAudioDevice() {
	FreeAudioQueue();
	Mix_CloseAudio();
	Mix_Quit();
}
