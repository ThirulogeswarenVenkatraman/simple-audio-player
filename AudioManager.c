#include "AudioManager.h"

extern SDL_Rect playDest;
extern SDL_Point mouse_pointer;

int music_state = 1;

void PauseAUDIO()
{
	SDL_GetMouseState(&mouse_pointer.x, &mouse_pointer.y);
	if (SDL_PointInRect(&mouse_pointer, &playDest) ||
		SDL_GetKeyboardState(NULL)[SDL_SCANCODE_AUDIOPLAY]) {
		
		if (!music_state) { 
			SDL_Log("Resumed\n");
			Mix_ResumeMusic();
			music_state = 1;
		}
		else {
			SDL_Log("Paused\n");
			Mix_PauseMusic();
			music_state = 0;
		}
	}
}
