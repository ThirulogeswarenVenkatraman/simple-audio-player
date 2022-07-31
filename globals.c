#include "SDL2/SDL.h"

#define PIXEL_SCALE 3

SDL_Point mouse_pointer;

int PX_SIZE = 16 * PIXEL_SCALE;

/* destination Rects */
const SDL_Rect rewindDest = { 20, 160, 16 * PIXEL_SCALE, 16 * PIXEL_SCALE };
const SDL_Rect playDest = { 150, 160, 16 * PIXEL_SCALE, 16 * PIXEL_SCALE };
const SDL_Rect forwardDest = { 190, 160, 16 * PIXEL_SCALE, 16 * PIXEL_SCALE };
const SDL_Rect stopDest = { 240, 160, 16 * PIXEL_SCALE, 16 * PIXEL_SCALE };
