#include "smp.h"
#include "animator.h"
#include "audiomanager.h"
#include "Windows.h"

const int window_screen_x = 480;
const int window_screen_y = 240;

/* Internals */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event evnt;
static HHOOK kbd;

extern music_props* current;
void throw_Error(const char *title, const char *errmsg) 
{ 
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errmsg, window);
    FreeResources();
    exit(-1);
}

static const Uint8 *KeyStates = NULL;
int isKeyDown(SDL_Scancode key) {
    if (KeyStates != 0) {
        if (KeyStates[key] == 1) {
            return 1;
        }
        else { return 0; }
    }
    return 0;
}

LRESULT CALLBACK outMultiMediaKeys(int nCode, 
WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT *mmkey = (KBDLLHOOKSTRUCT*)lParam;
    switch(wParam){
        case WM_KEYDOWN: {
            if(mmkey->vkCode == VK_MEDIA_PREV_TRACK) {
                current_prev_music(1, evnt);
            }
            if(mmkey->vkCode == VK_MEDIA_PLAY_PAUSE) {
                current_play_n_pause(1);
            }
            if(mmkey->vkCode == VK_MEDIA_NEXT_TRACK) {
                current_next_music(1);
            }
            break;
        }
        default: { currentFRAME(evnt); break;}
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
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

    kbd = SetWindowsHookEx(WH_KEYBOARD_LL, &outMultiMediaKeys, 0, 0);
    /* Open Audio Device */
    InitAudioDevice();

    /* Loading Textures */
    Init_Textures(renderer);
    
    return SDL_TRUE;
}

void EvntHandler() {
    audioex_updator();
    while(SDL_PollEvent(&evnt)) {
        switch(evnt.type) {
            case SDL_QUIT: {
                FreeResources();
                exit(0);
                break;
            }
            case SDL_DROPFILE: {
                if(isHeaderEmpty()){
                    load_header(evnt.drop.file);
                }else {
                    load_music_atEnd(evnt.drop.file);
                }
                break;
            }
            case SDL_KEYDOWN: {
                KeyStates = SDL_GetKeyboardState(NULL);
                if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
                    FreeResources();
                    exit(0);
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:  {
                if (evnt.button.button == SDL_BUTTON_LEFT) {
                    current_prev_music(0, evnt);
                    current_play_n_pause(0);
                    current_next_music(0);
                    clear_audio_queue();
                }
            }
            default: {
                currentFRAME(evnt);
                break;
            }
        }
    }  
}

void Render() {
    SDL_SetRenderDrawColor(renderer, 139, 155, 180, 255);
    SDL_RenderClear(renderer);
    Draw_Textures(renderer);
    SDL_RenderPresent(renderer);
}

void FreeResources() {
    UnhookWindowsHookEx(kbd);
    Free_Texture();
    FreeAudioQueue();
    DeinitAudioDevice();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    SDL_Log("Resource Freed\n");
}