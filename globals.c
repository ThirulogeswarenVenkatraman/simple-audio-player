#include "SDL2/SDL.h"

/* destination Rects */
/* 66 x 48 was 22 x 16 */
const SDL_Rect rewindDest = { 30, 146, 64, 46 };
/* 48 x 48 was 16 x 16 */
const SDL_Rect playDest = { 133, 146, 46, 46 };
/* 66 x 48 was 22 x 16 */
const SDL_Rect forwardDest = { 215, 146, 64, 46 };

const SDL_Rect cqDest = { 312, 154, 16 * 2, 16 * 2 }; /* clear */
