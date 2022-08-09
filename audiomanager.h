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

void LoadAudioFile(const char* filename);
void FreeAudioIfAny();

void PlaynPause(int byKey);

void Forward(int byKey);

/* linked list ig :) */
void next_music();

#endif // !AUDIO_MANAGER_H
