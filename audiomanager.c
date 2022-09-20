#include "include/audiomanager.h"

/* Externals */
extern SDL_Rect playDest;
extern SDL_Rect cqDest;
extern void throw_error(const char* title, const char* errmsg);
/* 1 -> Playing */
int music_state = 1;

// for getting the mouse position 
static SDL_Point mousepointer;
static void setup_audio_device() {
    if (!Mix_Init(MIX_INIT_MP3)) { // returns 0 on failure
		throw_error("Mixer Failed", Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)) {
		throw_error("Device Failed", Mix_GetError());
    }
	SDL_Log("Audio Device opened");
	Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void InitAudioDevice() {
	setup_audio_device();
}

void current_play_n_pause(int byKey) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &playDest) || byKey) {
		if (!music_state) {
			/* Resume */
			Mix_ResumeMusic();
			music_state = 1;
		}
		else {
			/* Pause It */
			Mix_PauseMusic();
			music_state = 0;
		}
	}
}

const SDL_Rect volbnDest = { 390, 60, 24, 146 };
const SDL_Rect volDest = { 390, 60, 24, 146 };
static void setVolume(int _volume) {
	Mix_VolumeMusic(_volume);
}

#define VOL_S 60
#define VOL_E 146
static int volume_pos = 0;
void volume_bar(SDL_Event _evnt) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &volDest)) {
		if (_evnt.button.state == SDL_PRESSED && _evnt.button.button == SDL_BUTTON_LEFT) {
			SDL_Log("ere");

		}
	}
}

void clear_audio_queue() { 
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &cqDest)) {
		FreeAudioQueue();
	}
}

void DeinitAudioDevice() {
	//FreeAudioQueue();
	Mix_CloseAudio();
	Mix_Quit();
}
