#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

void audioex_updator();

typedef struct music {
    struct music* prev;
    Mix_Music* _music;
    char* title;
    int mus_duration;
    struct music* next;
} music_props;

void InitAudioDevice();
void DeinitAudioDevice();

void load_header(const char* filename);
void load_at_last(const char* filename);
void FreeAudioQueue();

/* DLList :P */ 
SDL_bool isHeaderEmpty();
void current_prev_music(int byKey);
void current_play_n_pause(int byKey);
void current_next_music(int byKey);

void clear_audio_queue();

#endif

#ifndef AUDIO_EX_H

// for getting the mouse position 
static SDL_Point mousepointer;

extern void update_music_intels(int _dur);
extern void throw_error(const char* title, const char* errmsg);
extern void throw_warning(const char* title, const char* errmsg);

#endif 
