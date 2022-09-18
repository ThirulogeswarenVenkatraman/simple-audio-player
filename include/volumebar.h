#ifndef VOLUME_BAR_H
#define VOLUME_BAR_H

#include "SDL2/SDL.h"

void InitVolumeBar(SDL_Renderer* inrenderer);
void DrawVolumeBar(SDL_Renderer* inrenderer);
void update_volume();

void FreeVolumeBar();

#endif 
