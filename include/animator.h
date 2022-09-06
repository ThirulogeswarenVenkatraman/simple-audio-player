#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

void Init_Textures(SDL_Renderer* main_renderer);
void Draw_Textures(SDL_Renderer* main_renderer);
void Free_Texture();

void animate_frames(SDL_Event _evnt);

#endif // !ANIMATOR_H

#ifndef ANIMATION_EXTERN_USE

extern int music_state;
extern const char* active_title;
extern const SDL_Rect playDest;
extern const SDL_Rect forwardDest;
extern const SDL_Rect rewindDest;
extern const SDL_Rect cqDest;
extern const SDL_Rect barDest;

extern void throw_error(const char* title, const char* errmsg);

/* rewind */
#define PXR_FRAME_ONE (SDL_Rect){  0, 0, 22, 16 }
#define PXR_FRAME_TWO (SDL_Rect){ 22, 0, 22, 16 }
#define PXR_FRAME_THR (SDL_Rect){ 44, 0, 22, 16 }

/* playnpause */
#define PX_FRAME_ONE (SDL_Rect){  0, 0, 16, 16 }
#define PX_FRAME_TWO (SDL_Rect){ 16, 0, 16, 16 }
#define PX_FRAME_THR (SDL_Rect){ 32, 0, 16, 16 }
#define PX_FRAME_FOU (SDL_Rect){ 48, 0, 16, 16 }
#define PX_FRAME_FIV (SDL_Rect){ 64, 0, 16, 16 }
#define PX_FRAME_SIX (SDL_Rect){ 80, 0, 16, 16 }

/* forward */
#define PXF_FRAME_ONE (SDL_Rect){  0, 0, 22, 16 }
#define PXF_FRAME_TWO (SDL_Rect){ 22, 0, 22, 16 }
#define PXF_FRAME_THR (SDL_Rect){ 44, 0, 22, 16 }

/* clear queue */
#define PXCQ_FRAME_ONE (SDL_Rect){   0, 0, 69, 18 }
#define PXCQ_FRAME_TWO (SDL_Rect){  69, 0, 69, 18 }
#define PXCQ_FRAME_THR (SDL_Rect){ 138, 0, 69, 18 }

#define PXBAR_FRAME_ONE (SDL_Rect){0, 0, 36, 3};

#endif 



