#include "include/audiomanager.h"
#include "string.h"

#define _ERROR_H
#define _DEST_RECTS_H
#include "include/globals.h"

#ifdef WIN32
#define c_strdup _strdup
#else
#define c_strdup strdup
#endif /* native call */

#define _BAR_LIMIT 243.0f
/* music_bar properties */
static int _dynamic_pos = 0;
static float bar_addr = 0.0f;
extern SDL_FRect _music_bar;    
/* ===================== */

extern void update_music_intels(int _dur);

/* music nodes */
static music_props* header = NULL;
static music_props* tempo = NULL;
static music_props* new_node = NULL;
static music_props* current = NULL;
static music_props* next_addr = NULL;

/* export */
const char* active_title = "Empty Queue";

/* plays the music upon button_state */
static void play_now(Mix_Music* curr) {
    _music_bar.w = 0.0f;
    bar_addr = 0.0f;
    float temp_dur = (float)current->mus_duration;
    bar_addr = _BAR_LIMIT / temp_dur;
    
    active_title = current->title;
    Mix_HaltMusic();
    extern int music_state;
    if(music_state) { Mix_PlayMusic(curr, 0); }
    else {
        Mix_PlayMusic(curr, 0);
        Mix_PauseMusic();
    }
    update_music_intels(current->mus_duration);
}

SDL_bool isHeaderEmpty() {
    return (header == NULL ? SDL_TRUE : SDL_FALSE);
}

void load_header(const char* filename) {
    /* Load some audio */
    header = malloc(sizeof(music_props));
    if (header != NULL) {
        header->_music = Mix_LoadMUS(filename);
        if (!header->_music) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
                "invalid filename", filename, NULL);
            free(header);
            header = NULL;
        }
        else {
            header->prev = NULL;
            header->title = NULL;
            header->title = c_strdup(Mix_GetMusicTitleTag(header->_music));
            if (SDL_strlen(header->title) == 0)
            {
                header->title = c_strdup("album unknown");
            }
            header->mus_duration = (int)(Mix_MusicDuration(header->_music));
            header->next = NULL;
            current = header;
            play_now(current->_music);
        }
    }
    else {
        throw_warning("Allocation Error", filename);
        header = NULL;
    }

}

void load_at_last(const char* filename) {
    /* load music at the end */
    new_node = malloc(sizeof(music_props));
    if (new_node != NULL) {
        new_node->_music = Mix_LoadMUS(filename);
        if (!new_node->_music) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
                "invalid filename", filename, NULL);
            free(new_node);
            new_node = NULL;
        }
        else {
            tempo = header;
            /* we want tempo to be the last item*/
            while (tempo->next != NULL) { tempo = tempo->next; }
            new_node->prev = tempo;
            new_node->title = NULL;
            new_node->title = c_strdup(Mix_GetMusicTitleTag(new_node->_music));
            if (SDL_strlen(new_node->title) == 0)
            {
                new_node->title = c_strdup("album unknown");
            }
            new_node->mus_duration = (int)(Mix_MusicDuration(new_node->_music));
            new_node->next = NULL;
            tempo = header;
            while (tempo->next != NULL) {
                tempo = tempo->next;
            }
            if (tempo->next == NULL) {
                tempo->next = new_node;
                new_node = NULL;
            }
        }
    }
    else {
        throw_warning("Allocation Error", filename);
        new_node = NULL;
    }
}

/* clear the Queue */
void FreeAudioQueue() {
    active_title = "Empty Queue";
    Mix_HaltMusic();
    tempo = header;
    if (header != NULL) {
        header = NULL; 
        current = NULL;
        _music_bar.w = 0.0f;
        update_music_intels(0);
        while (tempo != NULL) {
            next_addr = tempo->next;
            free(tempo->title);
            tempo->title = NULL;
            Mix_FreeMusic(tempo->_music);
            tempo->_music = NULL;
            free(tempo);
            tempo = NULL;
            /* move to next object if any */
            tempo = next_addr;
        }
        tempo = next_addr = new_node = NULL;
        SDL_Log("Freed Audio Queue");
    }
    else { SDL_Log("Empty queue"); }
}

/* for getting the mouse pos */
static SDL_Point mousepointer;
/* points to the previous object if any */
void current_prev_music(int byKey) {
    SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
    if ((SDL_PointInRect(&mousepointer, &rewindDest) || byKey) &&
        header != NULL) {
        if ((current != NULL) && (current->prev != NULL)) {
            current = current->prev;
            play_now(current->_music);
        }   // else -> /* prev node is NULL */
    }
}

/* points to the next object if any */
void current_next_music(int byKey) {
    SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
    if ((SDL_PointInRect(&mousepointer, &forwardDest) || byKey) &&
        header != NULL) {
        if (current->next != NULL) {
            current = current->next;
            play_now(current->_music);
        }   // else -> /* next node is NULL */
    }
}

void audioex_updator() {
    if (current) {
        _dynamic_pos = (int)Mix_GetMusicPosition(current->_music);
    }
    if (header != NULL) {
        if (!Mix_PlayingMusic()) {
            /* if any music is loaded -> PLAY IT */
            if ((current != NULL) && (current->next != NULL)) {
                current = current->next;
                play_now(current->_music);
            }
        }
    }
    static int prev = 0;
    if (_dynamic_pos == 0) { prev = 0; _music_bar.w = 0.0f; }
    if (prev < _dynamic_pos) {
        SDL_Log("%d", bar_addr);
        _music_bar.w += bar_addr;
        prev = _dynamic_pos;
    }
}
