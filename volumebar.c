#include "include/volumebar.h"
#include "SDL2/SDL_image.h"

#define _ERROR_H
#include "include/globals.h"

static SDL_Rect src_rect = { 0, 0, 6, 36 };
static SDL_Rect dst_rect = { 390, 60, 24, 146 };

static SDL_Rect src_btn_rect = { 0, 0, 24, 5 };
static SDL_Rect dynamic_btn = { 390, 200, 24 , 5 }; /* dynamic */

/* skin */
static SDL_Texture* volume_bar = NULL;
static SDL_Texture* volume_btn = NULL;

extern int isKeyDown(SDL_Scancode key);

void InitVolumeBar(SDL_Renderer* inrenderer) {
	SDL_Surface* temp_bar_surf = IMG_Load("assets/volumebar.png");
	SDL_Surface* temp_btn_surf = IMG_Load("assets/volumebtn.png");

	if (!temp_bar_surf) { throw_error("Load Error", SDL_GetError()); }
	if (!temp_btn_surf) { throw_error("Load Error", SDL_GetError()); }

	volume_bar = SDL_CreateTextureFromSurface(inrenderer, temp_bar_surf);
	volume_btn = SDL_CreateTextureFromSurface(inrenderer, temp_btn_surf);
	
	SDL_FreeSurface(temp_bar_surf); temp_bar_surf = NULL;
	SDL_FreeSurface(temp_btn_surf); temp_btn_surf = NULL;
}

static SDL_Point r_mous = { 0, 0 };
void update_volume() {
	SDL_GetMouseState(&r_mous.x, &r_mous.y);
	if (SDL_PointInRect(&r_mous, &dst_rect)) {

	}
}

void DrawVolumeBar(SDL_Renderer* inrenderer) {
	SDL_RenderCopy(inrenderer, volume_bar, &src_rect, &dst_rect);
	SDL_RenderCopy(inrenderer, volume_btn, &src_btn_rect, &dynamic_btn);
}

void FreeVolumeBar() {
	SDL_DestroyTexture(volume_bar);
	volume_bar = NULL;
	SDL_DestroyTexture(volume_btn);
	volume_btn = NULL;
}