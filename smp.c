#include "include/smp.h"
#include "include/animator.h"
#include "include/audiomanager.h"
#include "include/volumebar.h"
#include "include/musicbar.h"

#ifdef WIN32
#include "include/dirent.h"
#else
#include "dirent.h"
#endif

/* window props */
#define WINDOW_SCREEN_X 444
#define WINDOW_SCREEN_Y 222

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static const Uint8* KeyStates = NULL;
static SDL_Event evnt;

static int isMouseInside = 0;
int isMouseDown = 0;

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
            animation_states();
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

static void drop_handler(const char* _dirname) {
    DIR* dir = opendir(_dirname);
    if (!dir) {
        if (isHeaderEmpty()) {
            load_header(_dirname);
        }
        else {
            load_at_last(_dirname);
        }
        return;
    }
    static char dirpath[100]; int i;
    SDL_zero(dirpath);
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
    char fullpath[256];
    struct dirent* ent = NULL;
    while ((ent = readdir(dir)) != NULL) {
        SDL_zero(fullpath);
        if (ent->d_type != DT_DIR) {
            SDL_strlcat(fullpath, dirpath, sizeof(fullpath)); // add the dir
            SDL_strlcat(fullpath, ent->d_name, sizeof(fullpath)); // and the name
            if (isHeaderEmpty()) {
                load_header(fullpath);
            }
            else {
                load_at_last(fullpath);
            }
        }
    }
    closedir(dir);
}

int InitSystem() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Init Failed: %s\n", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Init Failed", SDL_GetError(), NULL);
        SDL_Quit();
        exit(-1);
    }
    window = SDL_CreateWindow("SMP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    WINDOW_SCREEN_X, WINDOW_SCREEN_Y, SDL_WINDOW_HIDDEN);

    if(!window) {
        fprintf(stderr, "Window Creation Failed: %s\n", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window Creation Failed", SDL_GetError(), NULL);
        SDL_Quit();
        exit(-1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer) {
        fprintf(stderr, "Renderer Failed: %s\n", SDL_GetError());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Renderer Failed", SDL_GetError(), NULL);
        if (window != NULL) {
            SDL_DestroyWindow(window);
            window = NULL;
        }
        SDL_Quit();
        exit(-1);
    }
    
    if(TTF_Init()) { /* returns 0 on success */
        fprintf(stderr, "TTF Failed: %s\n", SDL_GetError());
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
    SDL_ShowWindow(window);
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
    animation_states();
    update_music_bar();
    audioex_updator();
    if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
        FreeResources();
        exit(0);
    }
    if (isMouseDown) {
        update_volume();
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

                    set_music_position_c();
                    isMouseDown = 1;
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                if (evnt.button.state == SDL_RELEASED) {
                    isMouseDown = 0;
                }
                break;
            }
            default: {
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