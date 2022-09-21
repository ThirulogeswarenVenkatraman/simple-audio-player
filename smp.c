#include "include/smp.h"
#include "include/animator.h"
#include "include/audiomanager.h"
#include "include/volumebar.h"
#include "include/musicbar.h"

/* window props */
#define WINDOW_SCREEN_X 480
#define WINDOW_SCREEN_Y 240

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static const Uint8* KeyStates = NULL;
static SDL_Event evnt;

void throw_error(const char* title, const char* errmsg);
void throw_warning(const char* title, const char* errmsg);

#ifdef WIN32
LRESULT CALLBACK outMultiMediaKeys(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT* mmkey = (KBDLLHOOKSTRUCT*)lParam;
    switch (wParam) {
        case WM_KEYDOWN: {
            if (mmkey->vkCode == VK_MEDIA_PREV_TRACK) {
                current_prev_music(1);
            }
            if (mmkey->vkCode == VK_MEDIA_PLAY_PAUSE) {
                current_play_n_pause(1);
            }
            if (mmkey->vkCode == VK_MEDIA_NEXT_TRACK) {
                current_next_music(1);
            }
            break;
        }
        default: {
            animation_states(evnt);
            break;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
#endif 

int isKeyDown(SDL_Scancode key) {
    if (KeyStates != 0) {
        if (KeyStates[key] == 1) {
            return 1;
        }
        else { return 0; }
    }
    return 0;
}

static void set_win_icon() {
    SDL_Surface* win_icon = NULL;
    win_icon = IMG_Load("assets/icon.png");
    if (!win_icon) {
        throw_error("Load Error", SDL_GetError());
    }
    SDL_SetWindowIcon(window, win_icon);
    SDL_FreeSurface(win_icon);
    win_icon = NULL;
    
}

SDL_bool InitSystem() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw_error("Init Failed", SDL_GetError());
    }
    window = SDL_CreateWindow("SMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_SCREEN_X, WINDOW_SCREEN_Y, 0);

    if(!window) {
        throw_error("Window Failed", SDL_GetError());
    }
    set_win_icon();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        throw_error("Renderer Failed", SDL_GetError());
    }
    
    if(TTF_Init()) { /* returns 0 on success */
        throw_error("TTF Failed", TTF_GetError());
    }
#ifdef WIN32
    kbd = SetWindowsHookEx(WH_KEYBOARD_LL, &outMultiMediaKeys, 0, 0);
#endif 

    /* Open Audio Device */
    InitAudioDevice();

    /* Loading Textures */
    Init_Textures(renderer);
    InitMusicBar(renderer);
    InitVolumeBar(renderer);

    return SDL_TRUE;
}

void Update() {
    update_music_bar();
    audioex_updator();
    if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
        FreeResources();
        exit(0);
    }

}

void EvntHandler() {
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT: {
                FreeResources();
                exit(0);
                break;
            }
            case SDL_DROPFILE: {
                if (isHeaderEmpty()) {
                    load_header(evnt.drop.file);
                }
                else {
                    load_at_last(evnt.drop.file);
                }
                SDL_free(evnt.drop.file);
                break;
            }
            case SDL_KEYDOWN: {
                KeyStates = SDL_GetKeyboardState(NULL);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (evnt.button.button == SDL_BUTTON_LEFT) {
                    current_prev_music(0);
                    current_play_n_pause(0);
                    current_next_music(0);
                    clear_audio_queue();

                    update_volume();
                    set_music_position_c();
                }
            }
            /* dont break the case */
            default: {
                animation_states(evnt);
                break;
            }
        }
    }
}        

void Render() {
    SDL_SetRenderDrawColor(renderer, 139, 155, 180, 255);
    SDL_RenderClear(renderer);
    /* draw here */
    DrawMusicBar(renderer);
    DrawVolumeBar(renderer);
    Draw_Textures(renderer);
    
    SDL_RenderPresent(renderer);
}

void FreeResources() {
#ifdef WIN32
    UnhookWindowsHookEx(kbd);
#endif 
    FreeAudioQueue();
    FreeMusicBar();
    FreeVolumeBar();
    Free_Texture();
    DeinitAudioDevice();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
    SDL_Log("Resource Freed\n");
}

void throw_error(const char* title, const char* errmsg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errmsg, window);
    FreeResources();
    exit(-1);
}

void throw_warning(const char* title, const char* errmsg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title, errmsg, window);
}