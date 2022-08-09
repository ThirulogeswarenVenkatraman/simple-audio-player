#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

typedef struct music {
    struct music* prev;
    Mix_Music* _music;
    const char* tile;
    int mus_position;
    struct music* next;
} music_props;

void InitAudioDevice();
void DeinitAudioDevice();

void PlaynPause(int byKey);

void Stop(int byKey);

#endif // !AUDIO_MANAGER_H
