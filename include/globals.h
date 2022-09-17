#ifdef _DEST_RECTS_H

extern const SDL_Rect rewindDest;
extern const SDL_Rect forwardDest;
extern const SDL_Rect rewindDest;
extern const SDL_Rect playDest;
extern const SDL_Rect cqDest;
extern const SDL_Rect barDest;

#endif 

#ifdef _ERROR_H 

extern void throw_error(const char* title, const char* errmsg);
extern void throw_warning(const char* title, const char* errmsg);

#endif 

#ifdef _FRAME_H /* only for animator unit */

extern int music_state;
extern const char* active_title;
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