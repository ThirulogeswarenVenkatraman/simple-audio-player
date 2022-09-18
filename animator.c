#include "include/animator.h"
#include "SDL2/SDL_mixer.h"

#define _ERROR_H
#define _DEST_RECTS_H
#include "include/globals.h"

/* externals */
extern int music_state;
extern const char* active_title;

/* Textures */
static SDL_Texture* _bar = NULL;
static SDL_Texture* _rewind = NULL;
static SDL_Texture* _play = NULL;
static SDL_Texture* _forward = NULL;
static SDL_Texture* _stop = NULL;
static SDL_Texture* _clearqueue = NULL;

/* font textures */
static SDL_Texture* _fmus_duration = NULL;
static SDL_Texture* _mus_intels = NULL;

/* music bar */
SDL_FRect _music_bar = { 31.0f, 143.0f, 0.0f, 4.0f };

/* don't free it here */
static SDL_Renderer* in_renderer = NULL;

static SDL_Texture* Load_Textures(const char* filename, SDL_Renderer* main_renderer) {
	static SDL_Texture* temp_texture = NULL;
	in_renderer = main_renderer;
	SDL_Surface* temp_surface = IMG_Load(filename);
	if (!temp_surface) {
		throw_error("Load Error", SDL_GetError());
	}
	temp_texture = SDL_CreateTextureFromSurface(main_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	return temp_texture;
}
static char outdur[] = { '0', ':', '0', '0', '\0' };
static void conv_to_min(int sec) {
	outdur[0] = outdur[2] = outdur[3] = '0';
	if(sec < 10 && sec > 0) { SDL_itoa(sec, &outdur[3], 10); }
	else if(sec > 10 && sec < 60) { SDL_itoa(sec, &outdur[2], 10); }
	else if(sec >= 60) {
		char temp_buffer[] = { '0', '0', '0', '\0' };
		int min = (int)sec / 60; // 1 min
		int afsec = sec - (min * 60); // 2 digits
		SDL_itoa(min, &temp_buffer[0], 10);
		if (afsec < 10) {
			temp_buffer[1] = '0';
			SDL_itoa(afsec, &temp_buffer[2], 10);
		}
		else {
			SDL_itoa(afsec, &temp_buffer[1], 10);
		}
		
		outdur[0] = temp_buffer[0];
		outdur[2] = temp_buffer[1];
		outdur[3] = temp_buffer[2];
	}
}

static TTF_Font* fonty_music_dur = NULL;
static TTF_Font* fonty_music_intel = NULL;
static void load_the_fonts(const char* filename) {
	fonty_music_dur = TTF_OpenFont(filename, 16);
	fonty_music_intel = TTF_OpenFont(filename, 23);
	if(!(fonty_music_dur || fonty_music_intel)) {
		throw_error("invalid font", TTF_GetError());
	}
}

static SDL_Rect mus_dur_Dest; static SDL_Rect mus_intel_Dest;
static void load_the_music_intel(int _duration) {
	if ((_fmus_duration != NULL) && (_mus_intels != NULL)) {
		SDL_DestroyTexture(_fmus_duration); _fmus_duration = NULL;
		SDL_DestroyTexture(_mus_intels); _mus_intels = NULL;
	}
	conv_to_min(_duration);
	SDL_Surface* temp_surf_duration = TTF_RenderText_Solid(fonty_music_dur, outdur, (SDL_Color){58, 68, 102, 255});
	SDL_Surface* temp_surf_music_intel = TTF_RenderText_Solid(fonty_music_intel, active_title, (SDL_Color){58, 68, 102, 255});
	/* destination */
	mus_dur_Dest = (SDL_Rect){286, 136, temp_surf_duration->w, temp_surf_duration->h };
	mus_intel_Dest = (SDL_Rect){30, 60, temp_surf_music_intel->w, temp_surf_music_intel->h };
	/* set the textures -> dynamic textures */
	_fmus_duration = SDL_CreateTextureFromSurface(in_renderer, temp_surf_duration);
	_mus_intels = SDL_CreateTextureFromSurface(in_renderer, temp_surf_music_intel);
	SDL_FreeSurface(temp_surf_duration);
	temp_surf_duration = NULL;
	SDL_FreeSurface(temp_surf_music_intel);
	temp_surf_music_intel = NULL;
}

void Init_Textures(SDL_Renderer* main_renderer) {
	load_the_fonts("assets/fonty.ttf");
	_rewind = Load_Textures("assets/rewind.png", main_renderer);
	_play = Load_Textures("assets/playpause.png", main_renderer);
	_forward = Load_Textures("assets/forward.png", main_renderer);
	_clearqueue = Load_Textures("assets/clearqueue.png", main_renderer);
	_bar = Load_Textures("assets/bar.png", main_renderer);

	load_the_music_intel(0);
}

void update_music_intels(int _dur) {
	load_the_music_intel(_dur);
}

/* Active states */
static SDL_Rect bar_src = { 0, 0, 36, 3 }; // static 

static SDL_Rect rewind_src = { 0, 0, 22, 16 }; // rewind 0 22 44 
static SDL_Rect play_src = { 0, 0, 16, 16 };   // playnpause 0 16 32 48 64 80 
static SDL_Rect forward_src = { 0, 0, 22, 16 }; // forward 0 22 44

static SDL_Rect clear_src = { 0, 0, 16, 16 }; // clear 0 16 32

void Draw_Textures(SDL_Renderer *main_renderer) { /* Render it */
	SDL_RenderCopy(main_renderer, _play, &play_src, &playDest);
	SDL_RenderCopy(main_renderer, _forward, &forward_src, &forwardDest);
	SDL_RenderCopy(main_renderer, _rewind, &rewind_src, &rewindDest);
	SDL_RenderCopy(main_renderer, _clearqueue, &clear_src, &cqDest);
	SDL_RenderCopy(main_renderer, _bar, &bar_src, &barDest);
	/* rendering fonts */
	SDL_RenderCopy(main_renderer, _fmus_duration, NULL, &mus_dur_Dest);
	SDL_RenderCopy(main_renderer, _mus_intels, NULL, &mus_intel_Dest);
	/* music bar */
	SDL_SetRenderDrawColor(main_renderer, 58, 68, 102, 255);
	SDL_RenderFillRectF(main_renderer, &_music_bar);
}

void Free_Texture() {
	if((_fmus_duration != NULL) && (_mus_intels != NULL)) {
		SDL_DestroyTexture(_fmus_duration); _fmus_duration = NULL;
		SDL_DestroyTexture(_mus_intels); _mus_intels = NULL;
	}
	SDL_DestroyTexture(_bar);
	_bar = NULL;
	SDL_DestroyTexture(_clearqueue);
	_clearqueue = NULL;
	SDL_DestroyTexture(_rewind);
	_rewind = NULL;
	SDL_DestroyTexture(_forward);
	_forward = NULL;
	SDL_DestroyTexture(_play);
	_play = NULL;
	TTF_CloseFont(fonty_music_intel);
	fonty_music_intel = NULL;
	TTF_CloseFont(fonty_music_dur);
	fonty_music_dur = NULL;
	in_renderer = NULL;
}

static SDL_Point mousepointer;
void animation_states(SDL_Event _evnt) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &playDest)) { /* play_n_pause */
		if (music_state) {
			play_src.x = 16;
			if (_evnt.button.state == SDL_PRESSED &&
				_evnt.button.button == SDL_BUTTON_LEFT) {
				play_src.x = 32;
			}
			else { play_src.x = 16; }
		}
		else {
			play_src.x = 64;
			if (_evnt.button.state == SDL_PRESSED &&
				_evnt.button.button == SDL_BUTTON_LEFT) {
				play_src.x = 80;
			}
			else { play_src.x = 64; }
		}
	}
	else if (SDL_PointInRect(&mousepointer, &forwardDest)) { /* forward */
		forward_src.x = 22;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			forward_src.x = 44;
		}
		else { forward_src.x = 22; }
	}
	else if (SDL_PointInRect(&mousepointer, &rewindDest)) { /* rewind */
		rewind_src.x = 22;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			rewind_src.x = 44;
		}
		else { rewind_src.x = 22; }
	}
	else if (SDL_PointInRect(&mousepointer, &cqDest)) { /* clear_queue */
		clear_src.x = 16;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			clear_src.x = 32;
		}
		else { clear_src.x = 16; }
	}
	else { /* Normal */
		if (music_state) { // 1 when playing
			play_src.x = 0;
		}
		else { // 0 if paused
			play_src.x = 48;
		}
		forward_src.x = rewind_src.x = clear_src.x = 0;
	}
}


