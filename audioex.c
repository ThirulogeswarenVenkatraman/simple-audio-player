#include "audiomanager.h"

extern int music_state;
extern SDL_Rect forwardDest;
extern SDL_Rect rewindDest;

static int once = 1;
static SDL_Point mousepointer;
static music_props* header = NULL;
static music_props* tempo = NULL;
static music_props* new_node = NULL;
static music_props* current = NULL;

/* export */
const char* active_title = "Empty Queue";

/* plays the music upon button_state */
extern void update_music_intels(int _dur);
static void play_now(Mix_Music* curr) { 
    active_title = current->title;
    if(music_state) { Mix_PlayMusic(curr, 0); }
    else {
        Mix_PlayMusic(curr, 0);
        Mix_PauseMusic();
    }
    update_music_intels(current->mus_duration);
}

static void load_at_last(const char* filename) {
    new_node = NULL;
    new_node = malloc(sizeof(music_props));
    if(new_node != NULL) {
        new_node->_music = Mix_LoadMUS(filename);
        if(!new_node->_music) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, 
            "invalid filename", filename, NULL);
        }
        else {
            tempo = header;
            /* we want tempo to be the last item*/
            while(tempo->next != NULL) { tempo = tempo->next; }
            new_node->prev = tempo;
            new_node->title = SDL_strdup(Mix_GetMusicTitleTag(new_node->_music));
            if (SDL_strlen(new_node->title) == 0)
            {
                new_node->title = "album unknown";
            }
            new_node->mus_duration = (int)(Mix_MusicDuration(new_node->_music));
            new_node->next = NULL;
            tempo = header;
            while(tempo->next != NULL) {
                tempo = tempo->next;
            }
            if(tempo->next == NULL) {
                tempo->next = new_node;
                new_node = NULL;
            }
        }
    }
    else { 
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, 
        "Allocation Error", filename, NULL);
        new_node = NULL;
    }
}

SDL_bool isHeaderEmpty() {
    return (header == NULL ? SDL_TRUE : SDL_FALSE);
}
void load_header(const char* filename) {
	/* Load some audio */
	header = malloc(sizeof(music_props));
    if(header != NULL) {
        header->_music = Mix_LoadMUS(filename);
        if(!header->_music) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, 
            "invalid filename", filename, NULL);
        }
        else {
            header->prev = NULL;
            header->title = SDL_strdup(Mix_GetMusicTitleTag(header->_music));
            if(SDL_strlen(header->title) == 0) 
            { header->title = "album unknown"; }
            header->mus_duration = (int)(Mix_MusicDuration(header->_music));
            header->next = NULL;
            current = header;
            play_now(current->_music);
        }
    }
   
}

static music_props* next_addr = NULL;
void FreeAudioQueue() {
    active_title = "Empty Queue";
    tempo = header;
    if (header != NULL) {
        Mix_HaltMusic();
        update_music_intels(0);
        while (tempo != NULL) {
            next_addr = tempo->next;
            Mix_FreeMusic(tempo->_music);
            tempo->_music = NULL;
            free(tempo);
            tempo = NULL;
            tempo = next_addr;
        }
        header = new_node = tempo = next_addr = NULL;
    }
    else { SDL_Log("Empty queue"); }
}

void view_list() {
    tempo = header;
    if(tempo == NULL) {
        SDL_Log("empty");
    }
    else {
        while(tempo != NULL) { /* visit every object */
            tempo = tempo->next;
        }
    }
}

void load_music_atEnd(const char* filename) {
    load_at_last(filename);
}

/* points to the next object if any */
void current_next_music(int byKey) {
    SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
    if( (SDL_PointInRect(&mousepointer, &forwardDest) || byKey) &&
        header != NULL) {
        if(current->next != NULL) {
            current = current->next;
            play_now(current->_music);
        }else {
            SDL_Log("ur at the end");
        }
    }
}

/* points to the previous object if any */
void current_prev_music(int byKey, SDL_Event _evnt) {
    SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
    if( (SDL_PointInRect(&mousepointer, &rewindDest) || byKey) && 
        header != NULL) {
        if ((current != NULL) && (current->prev != NULL)) {
            current = current->prev;
            play_now(current->_music);
        }
        else {
            SDL_Log("ur at the begining");
        }
    }
}

void audioex_updator() {
    if(header != NULL) {
        if(!Mix_PlayingMusic()) {
            if( current != NULL) {
                if(current->next != NULL) {
                    current = current->next;
                    play_now(current->_music);
                } else if(once) {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                    "Hungry", "Feed me Music...", NULL);
                    once = 0;
                }
            }
        }
    }
          
}
