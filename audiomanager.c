#include "include/audiomanager.h"

#ifdef WIN32
#include "include/dirent.h"
#else
#include "dirent.h"
#endif

/* Externals */
extern SDL_Rect playDest;
extern SDL_Rect cqDest;
extern void throw_error(const char* title, const char* errmsg);
/* 1 -> Playing */
int music_state = 1;

// for getting the mouse position 
static SDL_Point mousepointer;
static void setup_audio_device() {
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)) { // returns 0 on failure
		throw_error("Mixer Failed", Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)) {
		throw_error("Device Failed", Mix_GetError());
    }
	SDL_Log("Audio Device opened");
	Mix_VolumeMusic(100);
}

void default_location() {
	DIR* dir = opendir("music/");
	if (!dir) {
		return;
	}
	char fullpath[256];
	struct dirent* ent = NULL;
	while ((ent = readdir(dir)) != NULL) {
		SDL_zero(fullpath);
#ifdef WIN32
		SDL_strlcat(fullpath, "music\\", sizeof(fullpath));
#else
		SDL_strlcat(fullpath, "music/", sizeof(fullpath));
#endif
		if (ent->d_type != DT_DIR) {
			SDL_strlcat(fullpath, ent->d_name, sizeof(fullpath));
			if (isHeaderEmpty()) {
				load_header(fullpath);
			}
			else {
				load_at_last(fullpath);
			}
		}
	}
	closedir(dir);
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

void clear_audio_queue() { 
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &cqDest)) {
		FreeAudioQueue();
	}
}

void DeinitAudioDevice() {
	Mix_CloseAudio();
	Mix_Quit();
}
