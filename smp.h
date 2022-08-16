#ifndef SMP_H_
#define SMP_H_

#include "SDL2/SDL.h"

static SDL_bool state;

SDL_bool InitSystem();
void EvntHandler();
void Render();

void FreeResources();

#endif
