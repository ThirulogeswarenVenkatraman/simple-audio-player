#ifndef MUSIC_BAR_H
#define MUSIC_BAR_H

#include "SDL2/SDL.h"

void InitMusicBar(SDL_Renderer* inrenderer);
void DrawMusicBar(SDL_Renderer* inrenderer);
void update_music_bar();

void FreeMusicBar();

#endif // !MUSIC_BAR_H
