#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

void audioex_updator();

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

/* DLL :) */
SDL_bool isHeaderEmpty();
void view_list();
void load_music_atEnd(const char* filename);

// play <previous as>current music | rewind button
void current_prev_music(int byKey, SDL_Event _evnt);
// play <next as>current music | forward button
void current_next_music(int byKey);

#endif // !AUDIO_MANAGER_H
