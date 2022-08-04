#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

void PlayMusic(Mix_Music* _music, int times);

void PlaynPause();

#endif // !AUDIO_MANAGER_H
