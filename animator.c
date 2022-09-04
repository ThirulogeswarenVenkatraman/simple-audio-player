#include "animator.h"

#define EXTERN_USE

/* Textures */
static SDL_Texture* _bar = NULL;
static SDL_Texture* _rewind = NULL;
static SDL_Texture* _play = NULL;
static SDL_Texture* _forward = NULL;
static SDL_Texture* _stop = NULL;
static SDL_Texture* _clearqueue = NULL;

/* font_textures */
static SDL_Texture* _fmus_duration = NULL;
static SDL_Texture* _mus_intels = NULL;

static SDL_Renderer* in_renderer = NULL;
extern void throw_Error(const char* title, const char* errmsg);

static SDL_Texture* temp_texture = NULL;
static SDL_Texture* Load_Textures(const char* filename, SDL_Renderer* main_renderer) {
	in_renderer = main_renderer;
	SDL_Surface* temp_surface = IMG_Load(filename);
	if (!temp_surface) {
		throw_Error("Load Error", SDL_GetError());
	}
	temp_texture = SDL_CreateTextureFromSurface(main_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	return temp_texture;
}
static char outdur[] = { '0', ':', '0', '0', '\0' };
static void conv_to_min(int sec) {
	outdur[0] = outdur[2] = outdur[3] = '0';
	if(sec < 10 && sec != 0) { SDL_itoa(sec, &outdur[3], 10); }
	else if(sec > 10 && sec < 60) { SDL_itoa(sec, &outdur[2], 10); }
	else if(sec >= 60) {
		char temp_buffer[] = { '0', '0', '0', '\0' };
		int min = (int)sec / 60; // 1 min
		int afsec = sec - (min * 60); // 2 digits
		SDL_itoa(min, &temp_buffer[0], 10);
		SDL_itoa(afsec, &temp_buffer[1], 10);
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
		throw_Error("invalid font", TTF_GetError());
	}
}


static SDL_Rect mus_dur_Dest; static SDL_Rect mus_intel_Dest;
static void load_the_music_intel(int _duration) {
	if((_fmus_duration != NULL) && (_mus_intels != NULL)) {
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
	SDL_FreeSurface(temp_surf_music_intel);
}

void Init_Textures(SDL_Renderer* main_renderer) {
	load_the_fonts("assets/fonty.ttf");
	_rewind = Load_Textures("assets/rewind.png", main_renderer);
	_play = Load_Textures("assets/playpause.png", main_renderer);
	_forward = Load_Textures("assets/forward.png", main_renderer);
	_clearqueue = Load_Textures("assets/clearqueue.png", main_renderer);
	_bar = Load_Textures("assets/bar.png", main_renderer);
}

void update_music_intels(int _dur) {
	load_the_music_intel(_dur);
}

/* Active states */
static SDL_Rect RW_Active;
static SDL_Rect PL_Active;
static SDL_Rect FO_Active;
static SDL_Rect ST_Active;
static SDL_Rect BAR_Active;
static SDL_Rect CQ_Active;

void Draw_Textures(SDL_Renderer *main_renderer) {
	SDL_RenderCopy(main_renderer, _play, &PL_Active, &playDest);
	SDL_RenderCopy(main_renderer, _forward, &FO_Active, &forwardDest);
	SDL_RenderCopy(main_renderer, _rewind, &RW_Active, &rewindDest);
	SDL_RenderCopy(main_renderer, _clearqueue, &CQ_Active, &cqDest);
	SDL_RenderCopy(main_renderer, _bar, &BAR_Active, &barDest);
	/* rendering fonts */
	SDL_RenderCopy(main_renderer, _fmus_duration, NULL, &mus_dur_Dest);
	SDL_RenderCopy(main_renderer, _mus_intels, NULL, &mus_intel_Dest);
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
	SDL_DestroyRenderer(in_renderer);
}

static SDL_Point mousepointer;
void currentFRAME(SDL_Event _evnt) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &playDest)) { /* play_n_pause */
		if (music_state) {  
			PL_Active = PX_FRAME_TWO;
			if (_evnt.button.state == SDL_PRESSED && 
				_evnt.button.button == SDL_BUTTON_LEFT) {
				PL_Active = PX_FRAME_THR;
			}
			else if(_evnt.button.state == SDL_RELEASED &&
				_evnt.button.button == SDL_BUTTON_LEFT) {
				PL_Active = PX_FRAME_TWO;
			}
		}
		else {
			PL_Active = PX_FRAME_FIV;
			if (_evnt.button.state == SDL_PRESSED &&
				_evnt.button.button == SDL_BUTTON_LEFT) {
				PL_Active = PX_FRAME_SIX;
			}
			else if (_evnt.button.state == SDL_RELEASED &&
				_evnt.button.button == SDL_BUTTON_LEFT) {
				PL_Active = PX_FRAME_FIV;
			}
		}

	}
	else if (SDL_PointInRect(&mousepointer, &forwardDest)) { /* forward */
		FO_Active = PXF_FRAME_TWO;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			FO_Active = PXF_FRAME_THR;
		}
		else if(_evnt.button.state == SDL_RELEASED &&
			_evnt.button.button == SDL_BUTTON_LEFT)
		{
			FO_Active = PXF_FRAME_TWO;
		}
	}
	else if (SDL_PointInRect(&mousepointer, &rewindDest)) { /* rewind */
		RW_Active = PXR_FRAME_TWO;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			RW_Active = PXR_FRAME_THR;
		}
		else if(_evnt.button.state == SDL_RELEASED &&
			_evnt.button.button == SDL_BUTTON_LEFT)
		{
			RW_Active = PXR_FRAME_TWO;
		}
	}
	else if (SDL_PointInRect(&mousepointer, &cqDest)) { /* clear_queue */
		CQ_Active = PXCQ_FRAME_TWO;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			CQ_Active = PXCQ_FRAME_THR;
		}
		else if (_evnt.button.state == SDL_RELEASED &&
			_evnt.button.button == SDL_BUTTON_LEFT)
		{
			CQ_Active = PXCQ_FRAME_TWO;
		}
	}
	else { /* Normal */
		if (music_state) { // 1 when playing
			PL_Active = PX_FRAME_ONE;
		}
		else { // 0 if paused
			PL_Active = PX_FRAME_FOU;
		}
		FO_Active = PXF_FRAME_ONE;
		RW_Active = PXR_FRAME_ONE;
		CQ_Active = PXCQ_FRAME_ONE;
		BAR_Active = PXBAR_FRAME_ONE;
	}
}


