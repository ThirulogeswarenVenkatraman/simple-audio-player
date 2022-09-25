#ifndef SMP_H_
#define SMP_H_

#ifdef WIN32
#include <Windows.h>

/* handle hook */
static HHOOK kbd;
#endif 

#include "SDL2/SDL.h"

int InitSystem();

void Update();
void EvntHandler();
void Render();

void FreeResources();

#endif
