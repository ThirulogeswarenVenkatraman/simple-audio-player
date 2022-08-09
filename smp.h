#ifndef SMP_H
#define SMP_H_

#include "stdio.h"
#include "SDL2/SDL.h"

static SDL_bool state;

SDL_bool InitSystem();
void EvntHandler();
void Render();

void FreeResources();

#endif
