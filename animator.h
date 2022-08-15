#ifndef ANIMATOR_H
#define ANIMATOR_H

#include  "SDL2/SDL.h"

/* rewind */
#define PXR_FRAME_ONE (SDL_Rect){ 0, 0, 22, 16 }
#define PXR_FRAME_TWO (SDL_Rect){ 22, 0, 22, 16 }
#define PXR_FRAME_THR (SDL_Rect){ 44, 0, 22, 16 }

/* playnpause */
#define PX_FRAME_ONE (SDL_Rect){ 0, 0, 16, 16 }
#define PX_FRAME_TWO (SDL_Rect){ 16, 0, 16, 16 }
#define PX_FRAME_THR (SDL_Rect){ 32, 0, 16, 16 }
#define PX_FRAME_FOU (SDL_Rect){ 48, 0, 16, 16 }
#define PX_FRAME_FIV (SDL_Rect){ 64, 0, 16, 16 }
#define PX_FRAME_SIX (SDL_Rect){ 80, 0, 16, 16 }

/* forward */
#define PXF_FRAME_ONE (SDL_Rect){ 0, 0, 22, 16 }
#define PXF_FRAME_TWO (SDL_Rect){ 22, 0, 22, 16 }
#define PXF_FRAME_THR (SDL_Rect){ 44, 0, 22, 16 }

/* stop */
#define PXS_FRAME_ONE (SDL_Rect){ 0, 0, 16, 16 }
#define PXS_FRAME_TWO (SDL_Rect){ 16, 0, 16, 16 }
#define PXS_FRAME_THR (SDL_Rect){ 32, 0, 16, 16 }

void Init_Textures(SDL_Renderer* main_renderer);
void Draw_Textures(SDL_Renderer* main_renderer);
void Free_Texture();

void currentFRAME(SDL_Event _evnt);

#endif // !ANIMATOR_H


