#include "SDL2/SDL.h"

#define PIXEL_SCALE 3

/* destination Rects */
/* 66 x 48 was 22 x 16 */
const SDL_Rect rewindDest = { 30, 160, 66, 48 };
/* 48 x 48 was 16 x 16 */
const SDL_Rect playDest = { 130, 160, 48, 48 };
/* 66 x 48 was 22 x 16 */
const SDL_Rect forwardDest = { 212, 160, 66, 48 };

const SDL_Rect cqDest = { 312, 160, 16 * 2, 16 * 2 }; /* clear */

