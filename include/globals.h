#ifdef _DEST_RECTS_H

extern const SDL_Rect rewindDest;
extern const SDL_Rect forwardDest;
extern const SDL_Rect rewindDest;
extern const SDL_Rect playDest;
extern const SDL_Rect cqDest;
extern const SDL_Rect barDest;

#endif 

#ifdef _ERROR_H 

extern void throw_error(const char* title, const char* errmsg);
extern void throw_warning(const char* title, const char* errmsg);

#endif 
