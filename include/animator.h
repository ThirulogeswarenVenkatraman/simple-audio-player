#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

void Init_Textures(SDL_Renderer* main_renderer);
void Draw_Textures(SDL_Renderer* main_renderer);
void Free_Texture();

void animation_states(SDL_Event _evnt);

#endif 



