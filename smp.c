#include "smp.h"
#include "animator.h"
#include "AudioManager.h"

const int window_screen_x = 480;
const int window_screen_y = 240;

static const Uint8 *KeyStates = NULL;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event evnt;

static  Mix_Music* musi = NULL;

static void throw_Error(const char *title, const char *errmsg) 
{ 
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errmsg, NULL);
    exit(-1);

}

static int isKeyDown(SDL_Scancode key) {
    if(KeyStates != 0) {
        if(KeyStates[key] == 1) {
            return 1;
        }
        else { return 0; }
    }
    return 0;
}

static void KEUpdate() {
    if(isKeyDown(SDL_SCANCODE_ESCAPE)) {
        FreeResources();
        exit(0);
    }
}

SDL_bool InitSystem() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw_Error("Init Failed", SDL_GetError());
    }
    window = SDL_CreateWindow("SMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    window_screen_x, window_screen_y, 0);

    if(!window) {
        throw_Error("Window Failed", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        throw_Error("Renderer Failed", SDL_GetError());
    }

    if (!Mix_Init(MIX_INIT_MP3)) { // return 0 on failure
        throw_Error("Mixer Failed", Mix_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)) {
        throw_Error("Device Failed", Mix_GetError());
    }

    Mix_VolumeMusic(100);

    // Load Audio
    musi = Mix_LoadMUS("Enemy.mp3");
    if (!musi) {
        throw_Error("Invalid File", Mix_GetError());
    }

    // Play Music
    if (Mix_PlayMusic(musi, 0)) {
        throw_Error("Play Error", Mix_GetError());
    }
    
    // Loading Textures
    Load_Texture("playpause.png", renderer);

    return SDL_TRUE;
}

void EvntHandler() {
    while(SDL_PollEvent(&evnt)) {
        switch(evnt.type) {
            case SDL_QUIT: {
                FreeResources();
                exit(0);
                break;
            }
            case SDL_KEYDOWN: {
                KeyStates = SDL_GetKeyboardState(0);
                PauseAUDIO();
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                PauseAUDIO();
            }
            case SDL_MOUSEBUTTONUP: {

            }
            default: {
                HoverFRAME(evnt);
            }
        }
        
    }
    KEUpdate();
    
}

void Render() {
    
    SDL_SetRenderDrawColor(renderer, 139, 155, 180, 255);
    SDL_RenderClear(renderer);
    Draw_Them(renderer);
    SDL_RenderPresent(renderer);
}

void FreeResources() {
    Free_Texture();
    Mix_FreeMusic(musi);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    SDL_Log("Resource Freed\n");
}