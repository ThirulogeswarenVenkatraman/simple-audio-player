#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

typedef struct music {
    struct music* prev;
    Mix_Music* _music;
    const char* title;
    int mus_position;
    struct music* next;
} music_props;

void InitAudioDevice();
void DeinitAudioDevice();

void LoadAudioFile(const char* filename);
void FreeAudioIfAny();

void PlaynPause(int byKey);

/* linked list ig :) */
SDL_bool isHeaderEmpty();
void view_list();
void load_music_atEnd(const char* filename);

// play current music | forward button
void current_next_music(int byKey);

#endif // !AUDIO_MANAGER_H
