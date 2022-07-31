#include "animator.h"
#include "SDL2/SDL_image.h"

/* External */
extern int music_state;
extern SDL_Point mouse_pointer;

extern SDL_Rect playDest;
extern SDL_Rect stopDest;


static SDL_Rect PL_Active;
static SDL_Rect ST_Active;

static SDL_Texture* pause = NULL;
static SDL_Texture* stop = NULL;

static void animator_Error(const char* title, const char* errmsg) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, errmsg, NULL);
}

void Load_Texture(SDL_Renderer *main_renderer) {
	SDL_Surface* temp_surface = IMG_Load("playpause.png");
	if (!temp_surface) {
		animator_Error("Animator Error", SDL_GetError());
	}
	pause = SDL_CreateTextureFromSurface(main_renderer, temp_surface);
	if (!pause) {
		animator_Error("Texture Error", SDL_GetError());
	}
	SDL_FreeSurface(temp_surface);
}

void Draw_Them(SDL_Renderer *main_renderer) {
	SDL_RenderCopy(main_renderer, pause, &PL_Active, &playDest);
	SDL_RenderCopy(main_renderer, stop, &ST_Active, &stopDest);

}

void Free_Texture() {
	SDL_DestroyTexture(pause);
	pause = NULL;
}


void HoverFRAME(SDL_Event _evnt) {

	SDL_GetMouseState(&mouse_pointer.x, &mouse_pointer.y);
	if (SDL_PointInRect(&mouse_pointer, &playDest)) { // hovering
		if (music_state) {  
			PL_Active = PX_FRAME_TWO;
			if (_evnt.button.state == SDL_PRESSED) {
				PL_Active = PX_FRAME_THR;
			}
			else if(_evnt.button.state == SDL_RELEASED) {
				PL_Active = PX_FRAME_TWO;
			}
		}
		else {
			PL_Active = PX_FRAME_FIV;
			if (_evnt.button.state == SDL_PRESSED) {
				PL_Active = PX_FRAME_SIX;
			}
			else if (_evnt.button.state == SDL_RELEASED) {
				PL_Active = PX_FRAME_FIV;
			}
		}

	}
	else if (SDL_PointInRect(&mouse_pointer, &stopDest)) {
		
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


