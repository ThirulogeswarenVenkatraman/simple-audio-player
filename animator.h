#ifndef ANIMATOR_H
#define ANIMATOR_H

#include  "SDL2/SDL.h"

#define PX_FRAME_ONE (SDL_Rect){ 0, 0, 16, 16 }
#define PX_FRAME_TWO (SDL_Rect){ 16, 0, 16, 16 }
#define PX_FRAME_THR (SDL_Rect){ 32, 0, 16, 16 }
#define PX_FRAME_FOU (SDL_Rect){ 48, 0, 16, 16 }
#define PX_FRAME_FIV (SDL_Rect){ 64, 0, 16, 16 }
#define PX_FRAME_SIX (SDL_Rect){ 80, 0, 16, 16 }

#define PXS_FRAME_ONE (SDL_Rect){ 0, 0, 16, 16 }
#define PXS_FRAME_TWO (SDL_Rect){ 16, 0, 16, 16 }
#define PXS_FRAME_THR (SDL_Rect){ 32, 0, 16, 16 }

void Load_Texture(const char* filename, SDL_Renderer* main_renderer);

void Draw_Them(SDL_Renderer* main_renderer);

void Free_Texture();

void HoverFRAME(SDL_Event _evnt);

#endif // !ANIMATOR_H


