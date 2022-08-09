#include "smp.h"
#include "animator.h"
#include "audiomanager.h"

const int window_screen_x = 480;
const int window_screen_y = 240;

static const Uint8 *KeyStates = NULL;

static SDL_Point mouse_pointer;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event evnt;

static  Mix_Music* musi = NULL;

extern int music_state;
void throw_Error(const char *title, const char *errmsg) 
{ 
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errmsg, window);
    FreeResources();
    exit(-1);
}

int isKeyDown(SDL_Scancode key) {
    if (KeyStates != 0) {
        if (KeyStates[key] == 1) {
            return 1;
        }
        else { return 0; }
    }
    return 0;
}

SDL_bool InitSystem() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw_Error("Init Failed", SDL_GetError());
    }
    window = SDL_CreateWindow("SMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    window_screen_x, window_screen_y, SDL_WINDOW_INPUT_FOCUS);

    if(!window) {
        throw_Error("Window Failed", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        throw_Error("Renderer Failed", SDL_GetError());
    }

    // Loading Textures
    Init_Textures(renderer);
    
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
                KeyStates = SDL_GetKeyboardState(NULL);
                if (isKeyDown(SDL_SCANCODE_AUDIOPLAY)) {
                    
                }
                if (isKeyDown(SDL_SCANCODE_AUDIOSTOP)) {

                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:  {
                if (evnt.button.button == SDL_BUTTON_LEFT) {

                }
            }
            default: {
                HoverFRAME(evnt);
                break;
            }
        }
    }
    if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
        FreeResources();
        exit(0);
    }
}

void Render() {
    
    SDL_SetRenderDrawColor(renderer, 139, 155, 180, 255);
    SDL_RenderClear(renderer);
    Draw_Textures(renderer);
    SDL_RenderPresent(renderer);
}

void FreeResources() {
    Free_Texture();
    DeinitAudioDevice();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    SDL_Log("Resource Freed\n");
}