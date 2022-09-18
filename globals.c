#include "SDL2/SDL.h"

#define PIXEL_SCALE 3

/* destination Rects */
const SDL_Rect rewindDest = { 30, 160, 22 * PIXEL_SCALE, 16 * PIXEL_SCALE };
const SDL_Rect playDest = { 130, 160, 16 * PIXEL_SCALE, 16 * PIXEL_SCALE };
const SDL_Rect forwardDest = { 212, 160, 22 * PIXEL_SCALE, 16 * PIXEL_SCALE };

const SDL_Rect cqDest = { 312, 160, 16 * 2, 16 * 2 }; /* clear */
const SDL_Rect barDest = { 28, 139, 252, 12 }; /* bar */

