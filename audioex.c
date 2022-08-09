
#include "audiomanager.h"

static music_props* header = NULL;
static music_props* current = NULL;
static music_props* tempo = NULL;

void LoadAudioFile(const char* filename) {
    FreeAudioIfAny();
	/* Load some audio */
	header = malloc(sizeof(music_props));
    if(header != NULL) {
        header->_music = Mix_LoadMUS(filename);
        if(!header->_music) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, 
            "invalid filename", filename, NULL);
        }
        else {
            header->tile = Mix_GetMusicAlbumTag(header->_music);
        }
        Mix_PlayMusic(header->_music, 0);
        SDL_Log("Playing %s", header->tile);
    }
}

void FreeAudioIfAny() {
    if(header != NULL) {  /* deallocate header */
        SDL_Log("Freeing Audio");
        Mix_FreeMusic(header->_music);
        free(header);
        header = NULL;
    }
}

void next_music() {

}


