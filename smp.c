#include "include/smp.h"
#include "include/animator.h"
#include "include/audiomanager.h"
#include "include/volumebar.h"
#include "include/musicbar.h"

#include <stdio.h>

#ifdef WIN32
#include "SDL2/dirent.h"
#else
#include "dirent.h"
#endif

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

void drop_file(const char* _filename) {
    if (isHeaderEmpty()) {
        load_header(_filename);
    }
    else {
        load_at_last(_filename);
    }
}

static void drop_handler(const char* _dirname) {
    DIR* dir = opendir(_dirname);
    if (!dir) {
        drop_file(_dirname);
        return;
    }
    char dirpath[100]; int i;
    for (i = 0; *_dirname != '\0'; i++) {
        dirpath[i] = *_dirname;
        _dirname++;
    }
#ifdef WIN32 /* [i] will be NULL */
    dirpath[i] = '\\';
#else
    dirpath[i] = '/';
#endif 
    dirpath[i + 1] = '\0';
    /* got the dir-path */
    struct dirent* ent;
    char fullpath[100];
    while ((ent = readdir(dir)) != NULL) {
        SDL_zero(fullpath);
        if (ent->d_type != DT_DIR) {
            SDL_strlcat(fullpath, dirpath, 100); // add the dir
            SDL_strlcat(fullpath, ent->d_name, 100); // and the name
            drop_file(fullpath);
        }
    }
    closedir(dir);
}

int InitSystem() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Init Failed: %s", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", SDL_GetError(), NULL);
        SDL_Quit();
        exit(-1);
    }
    window = SDL_CreateWindow("SMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_SCREEN_X, WINDOW_SCREEN_Y, 0);

    if(!window) {
        fprintf(stderr, "Window Creation Failed: %s", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Creation Failed", SDL_GetError(), NULL);
        SDL_Quit();
        exit(-1);
    }
    set_win_icon();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        fprintf(stderr, "Renderer Failed: %s", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Failed", SDL_GetError(), NULL);
        if (window != NULL) {
            SDL_DestroyWindow(window);
            window = NULL;
        }
        SDL_Quit();
        exit(-1);
    }
    
    if(TTF_Init()) { /* returns 0 on success */
        fprintf(stderr, "TTF Failed: %s", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "TTF Failed", SDL_GetError(), window);
        if (renderer != NULL) {
            SDL_DestroyRenderer(renderer);
            renderer = NULL;
        }
        if (window != NULL) {
            SDL_DestroyWindow(window);
            window = NULL;
        }
        TTF_Quit();
        SDL_Quit();
        exit(-1);
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

    default_location();
    return 1;
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
                drop_handler(evnt.drop.file);
                SDL_free(evnt.drop.file);
                break;
            }
            case SDL_KEYDOWN: {
                KeyStates = SDL_GetKeyboardState(NULL);
                break;
            }
            case SDL_MOUSEWHEEL: {
                if (evnt.wheel.y > 0) {
                    onScrollUpie();
                }
                else if (evnt.wheel.y < 0) {
                    onScrollDownie();
                }
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
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
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