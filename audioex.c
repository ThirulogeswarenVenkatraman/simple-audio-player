#include "stdio.h"
#include "audiomanager.h"
#include "SDL2/SDL_filesystem.h"

extern int music_state;
extern SDL_Rect forwardDest;
extern SDL_Rect rewindDest;

static int once = 1;
static SDL_Point mousepointer;
static music_props* header = NULL;
static music_props* tempo = NULL;
static music_props* new_node = NULL;

music_props* current = NULL;

/* plays the music upon button_state */
static void play_now(Mix_Music* curr) { 
    if(music_state) { Mix_PlayMusic(curr, 0); }
    else {
        Mix_PlayMusic(curr, 0);
        Mix_PauseMusic();
    }
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
            new_node->title = Mix_GetMusicTitle(new_node->_music);
            new_node->next = NULL;
            while(tempo->next != NULL) {
                tempo = tempo->next;
            }
            if(tempo->next == NULL) {
                tempo->next = new_node;
                SDL_Log("Loaded %s", new_node->title);
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
    if(header == NULL) {
        return SDL_TRUE;
    } else { return SDL_FALSE; }
    //return header == NULL ? SDL_TRUE : SDL_FALSE;
}
void LoadAudioFile(const char* filename) {
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
            header->title = Mix_GetMusicAlbumTag(header->_music);
            header->next = NULL;
            SDL_Log("Loading header -> %s", header->title);
            current = header;
            play_now(current->_music);
        }
    }
   
}

void FreeAudioIfAny() {
    if(header != NULL) {  /* deallocate header */
        music_props* next_addr = NULL;
        SDL_Log("Freed Audio");
        tempo = header;
        while(tempo != NULL) {
            Mix_FreeMusic(tempo->_music);
            next_addr = tempo->next;
            free(tempo);
            tempo = next_addr;
        }
        header = NULL;
    }
}

void view_list() {
    tempo = header;
    if(tempo == NULL) {
        SDL_Log("empty");
    }
    else {
        int i = 0;
        while(tempo != NULL) { /* visit every object */
            printf("Title[%d]: %s\n", i, tempo->title);
            tempo = tempo->next; i++;
        }
    }
}

void load_music_atEnd(const char* filename) {
    tempo = header;
    while(tempo->next != NULL) { /* points to last object*/ 
        tempo = tempo->next;
    }
    if(tempo->next == NULL) {
        load_at_last(filename);
    }
}

/* points to the next object if any */
void current_next_music(int byKey) {
    SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
    if((SDL_PointInRect(&mousepointer, &forwardDest) || byKey) &&
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
    if(SDL_PointInRect(&mousepointer, &rewindDest) || byKey) {
        if(_evnt.button.clicks == 1) {
            SDL_Log("Single TAP");
            Mix_RewindMusic();
        }
        else if(_evnt.button.clicks > 1) {
            SDL_Log("Double TAP");
        }
    }
}

void audioex_updator() {
    if(!Mix_PlayingMusic()) {
        if( current != NULL) {
            if(current->next != NULL) {
                current = current->next;
                Mix_PlayMusic(current->_music, 0);
            } else if(once) {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                "Hungry", "Feed me Music...", NULL);
                once = 0;
            }
        }
    }
          
}
