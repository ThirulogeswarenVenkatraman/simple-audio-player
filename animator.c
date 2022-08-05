#include "animator.h"
#include "SDL2/SDL_image.h"

/* External */
extern int music_state;
extern SDL_Rect playDest;
extern SDL_Rect stopDest;

/* Active states */
static SDL_Rect RW_Active;
static SDL_Rect PL_Active;
static SDL_Rect FO_Active;
static SDL_Rect ST_Active;

/* Textures */
static SDL_Texture* _rewind = NULL;
static SDL_Texture* play = NULL;
static SDL_Texture* forward = NULL;
static SDL_Texture* stop = NULL;

extern void throw_Error(const char* title, const char* errmsg);

static SDL_Texture* Load_Textures(const char* filename, SDL_Renderer* main_renderer) {
	SDL_Surface* temp_surface = IMG_Load(filename);
	if (!temp_surface) {
		throw_Error("Load Error", SDL_GetError());
	}
	SDL_Texture* temp_texture = NULL;
	temp_texture = SDL_CreateTextureFromSurface(main_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	return temp_texture;
}

void INIT_Textures(SDL_Renderer* main_renderer) {
	play = Load_Textures("playpause.png", main_renderer);
	stop = Load_Textures("stop.png", main_renderer);
}


void Draw_Them(SDL_Renderer *main_renderer) {
	SDL_RenderCopy(main_renderer, play, &PL_Active, &playDest);
	SDL_RenderCopy(main_renderer, stop, &ST_Active, &stopDest);

}

void Free_Texture() {
	SDL_DestroyTexture(play);
	play = NULL;
}

static SDL_Point mousepointer;
void HoverFRAME(SDL_Event _evnt) {
	SDL_GetMouseState(&mousepointer.x, &mousepointer.y);
	if (SDL_PointInRect(&mousepointer, &playDest)) { // hovering
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
	else if (SDL_PointInRect(&mousepointer, &stopDest)) {
		ST_Active = PXS_FRAME_TWO;
		if (_evnt.button.state == SDL_PRESSED &&
			_evnt.button.button == SDL_BUTTON_LEFT) {
			ST_Active = PXS_FRAME_THR;
			PL_Active = PX_FRAME_FOU;
		}
		else if(_evnt.button.state == SDL_RELEASED &&
			_evnt.button.button == SDL_BUTTON_LEFT)
		{
			ST_Active = PXS_FRAME_TWO;
		}
	}
	else { /* Normal */
		if (music_state) { // 1 when playing
			PL_Active = PX_FRAME_ONE;
		}
		else { // 0 if paused
			PL_Active = PX_FRAME_FOU;
		}
		ST_Active = PXS_FRAME_ONE;
	}
}


