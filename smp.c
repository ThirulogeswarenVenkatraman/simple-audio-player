#include "smp.h"

#define WIN_X 480
#define WIN_Y 240

static const Uint8 *KeyStates = NULL;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event evnt;

static SDL_bool throw_Error(const char *title, const char *errmsg) { 
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errmsg, NULL);
    return SDL_FALSE;
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
        return throw_Error("Init Failed", SDL_GetError());
    }
    window = SDL_CreateWindow("SMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WIN_X, WIN_Y, 0);

    if(!window) {
        return throw_Error("Window Failed", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        return throw_Error("Renderer Failed", SDL_GetError());
    }
    
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
                break;
            }
        }
    }
    KEUpdate();
}

void Render() {
    SDL_RenderPresent(renderer);

    SDL_RenderClear(renderer);
}

void FreeResources() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    printf("Resource Freed\n");
}