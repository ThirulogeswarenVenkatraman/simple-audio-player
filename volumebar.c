#include "include/volumebar.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

static int val = 0;

static SDL_Rect src_rect = { 0, 0, 6, 36 };
static SDL_Rect dst_rect = { 390, 60, 24, 128 };
/* dynamic -> y and h */
static SDL_Rect dynamic_btn = { 390, 187, 24 , 1 };
/* skin */
static SDL_Texture* volume_bar = NULL;
static TTF_Font* fonty = NULL;
static SDL_Rect font_dst = { 0,0,0,0 };
static SDL_Texture* volume_indicator = NULL;


static SDL_Renderer* in_ren = NULL;

extern void throw_error(const char* title, const char* errmsg);

void InitVolumeBar(SDL_Renderer* inrenderer) {
	in_ren = inrenderer;
	SDL_Surface* temp_bar_surf = IMG_Load("assets/volumebar.png");
	if (!temp_bar_surf) {
		throw_error("Load Error", SDL_GetError());
	}
	volume_bar = SDL_CreateTextureFromSurface(inrenderer, temp_bar_surf);
	SDL_FreeSurface(temp_bar_surf); 
	temp_bar_surf = NULL;
	dynamic_btn.h = -100;
	val = 100;

	/* fonts */
	fonty = TTF_OpenFont("assets/fonty.ttf", 13);
	SDL_Surface* temp_surf_font = TTF_RenderText_Solid(fonty,
		"100", (SDL_Color){ 58, 68, 102, 255 });
	volume_indicator = SDL_CreateTextureFromSurface(inrenderer, temp_surf_font);
	font_dst = (SDL_Rect){ 390, 189, temp_surf_font->w, temp_surf_font->h };
	SDL_FreeSurface(temp_surf_font);
	temp_surf_font = NULL;
}


static void update_volume_intel() {
	if (volume_indicator != NULL) {
		SDL_DestroyTexture(volume_indicator);
		volume_indicator = NULL;
	}
	char volume_ind[4] = { '0', '0', '0', '\0' };
	SDL_itoa(val, volume_ind, 10);
	SDL_Surface* temp_surf_font = TTF_RenderText_Solid(fonty, volume_ind, (SDL_Color){ 58, 68, 102, 255 });
	volume_indicator = SDL_CreateTextureFromSurface(in_ren, temp_surf_font);
	font_dst = (SDL_Rect){ 390, 189, temp_surf_font->w, temp_surf_font->h };
	SDL_FreeSurface(temp_surf_font);
	temp_surf_font = NULL;
}

static SDL_Point r_mous = { 0, 0 };
void update_volume() {
	SDL_GetMouseState(&r_mous.x, &r_mous.y);
	if (SDL_PointInRect(&r_mous, &dst_rect)) { // pos -> 60 to 187
		val = (int)(r_mous.y - dst_rect.y); // 0 to 128
		val = 128 - val;
		if (val < 128) {
			dynamic_btn.h = -val;
		}
		SDL_Log("%d", val);
		Mix_VolumeMusic(val);
		update_volume_intel();
	}
}

void onScrollUpie() {
	SDL_GetMouseState(&r_mous.x, &r_mous.y);
	if (SDL_PointInRect(&r_mous, &dst_rect)) {
		val += 6;
		if (val < 128) {
			dynamic_btn.h -= 6;
		}
		else {
			val = 128;
			dynamic_btn.h = -126;
		}
		Mix_VolumeMusic(val);
		update_volume_intel();
	}
}

void onScrollDownie() {
	SDL_GetMouseState(&r_mous.x, &r_mous.y);
	if (SDL_PointInRect(&r_mous, &dst_rect)) {
		val -= 6;
		if (val > 0) {
			dynamic_btn.h += 6;
		}
		else {
			val = 0;
			dynamic_btn.h = -1;
		}
		Mix_VolumeMusic(val);
		update_volume_intel();
	}
}


void DrawVolumeBar(SDL_Renderer* inrenderer) {
	SDL_RenderCopy(inrenderer, volume_bar, &src_rect, &dst_rect);
	SDL_RenderCopy(inrenderer, volume_indicator, NULL, &font_dst);
	SDL_SetRenderDrawColor(inrenderer, 58, 68, 102, 255);
	SDL_RenderFillRect(inrenderer, &dynamic_btn);
}

void FreeVolumeBar() {
	in_ren = NULL;
	TTF_CloseFont(fonty);
	fonty = NULL;
	SDL_DestroyTexture(volume_indicator); 
	volume_indicator = NULL;
	SDL_DestroyTexture(volume_bar);
	volume_bar = NULL;
}