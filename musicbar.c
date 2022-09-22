#include "include/musicbar.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#define _BAR_LIMIT 243.0f

extern int music_state;
extern float bar_addr;
extern void throw_error(const char* title, const char* errmsg);

static int _live_pos;
static SDL_Rect bar_src = { 0, 0, 36, 3 }; // static 
const SDL_Rect bar_dst = { 28, 139, 252, 12 }; /* bar */
/* music bar dynamic */
SDL_Rect changer_bar = { 31, 139, 243, 12 };
SDL_FRect _music_bar = { 31.0f, 143.0f, 0.0f, 4.0f };

static SDL_Texture* _bar = NULL;

void InitMusicBar(SDL_Renderer* inrenderer) {
	SDL_Surface* temp_surf = NULL;	
	temp_surf = IMG_Load("assets/bar.png");
	if (!temp_surf) {
		throw_error("Load Error", SDL_GetError());
	}
	_bar = SDL_CreateTextureFromSurface(inrenderer, temp_surf);
	SDL_FreeSurface(temp_surf);
	temp_surf = NULL;
}

void DrawMusicBar(SDL_Renderer* inrenderer) {
	SDL_RenderCopy(inrenderer, _bar, &bar_src, &bar_dst);
	SDL_SetRenderDrawColor(inrenderer, 58, 68, 102, 255);
	SDL_RenderFillRectF(inrenderer, &_music_bar);
}
static int prev = 0;
extern int dyn_bar_pos();
void update_music_bar() {
	if (music_state) {
		_live_pos = dyn_bar_pos();
		if (_live_pos == 0) { prev = 0; _music_bar.w = 0.0f; }
		if (prev < _live_pos) {
			SDL_Log("%d", bar_addr);
			_music_bar.w += bar_addr;
			prev = _live_pos;
		}
	}
}

void set_music_position_c() {
	static SDL_Point mouse_pos;
	static int temp_prev;
	static double temp_live_pos;
	static float accumulator;
	if (music_state) {
		SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
		if (SDL_PointInRect(&mouse_pos, &changer_bar) && bar_addr) {
			static int from_bar;
			from_bar = mouse_pos.x - changer_bar.x;
			for (float from = 0.0f, till = (float)from_bar;
				from < till; from += bar_addr) { /* respect to musicbar <rect> */
				accumulator += bar_addr;
				temp_prev++;
			}
			prev = temp_prev;
			temp_live_pos = (double)(temp_prev + 1);
			Mix_SetMusicPosition(temp_live_pos);
			_music_bar.w = accumulator;
			accumulator = 0.0f;
			temp_live_pos = 0.0f;
			temp_prev = 0;
		}
	}
}

void FreeMusicBar() {
	SDL_DestroyTexture(_bar);
	_bar = NULL;
}
