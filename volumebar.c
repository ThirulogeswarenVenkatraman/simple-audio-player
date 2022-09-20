#include "include/volumebar.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#define INVERSE_ 128

static SDL_Rect src_rect = { 0, 0, 6, 36 };
static SDL_Rect dst_rect = { 390, 60, 24, 128 };
/* dynamic -> y and h */
static SDL_Rect dynamic_btn = { 390, 187, 24 , 1 };
/* skin */
static SDL_Texture* volume_bar = NULL;

extern void throw_error(const char* title, const char* errmsg);

void InitVolumeBar(SDL_Renderer* inrenderer) {
	SDL_Surface* temp_bar_surf = IMG_Load("assets/volumebar.png");
	if (!temp_bar_surf) {
		throw_error("Load Error", SDL_GetError());
	}
	volume_bar = SDL_CreateTextureFromSurface(inrenderer, temp_bar_surf);
	SDL_FreeSurface(temp_bar_surf); 
	temp_bar_surf = NULL;
}

static SDL_Point r_mous = { 0, 0 };
void update_volume() {
	static int val;
	SDL_GetMouseState(&r_mous.x, &r_mous.y);
	if (SDL_PointInRect(&r_mous, &dst_rect)) { // pos -> 60 to 187
		val = (int)(r_mous.y - dst_rect.y); // 0 to 128
		val = INVERSE_ - val;
		if (val < 128) {
			dynamic_btn.h = -val;
		}
		SDL_Log("%d", val);
		Mix_VolumeMusic(val);
	}
}

void DrawVolumeBar(SDL_Renderer* inrenderer) {
	SDL_RenderCopy(inrenderer, volume_bar, &src_rect, &dst_rect);
	SDL_SetRenderDrawColor(inrenderer, 58, 68, 102, 255);
	SDL_RenderFillRect(inrenderer, &dynamic_btn);
}

void FreeVolumeBar() {
	SDL_DestroyTexture(volume_bar);
	volume_bar = NULL;
}