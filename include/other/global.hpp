#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gMainFont;
extern TTF_Font *gTitleFont;
extern SDL_FRect gTileClips[];
extern float gDeltaTime;