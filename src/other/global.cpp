#include "../../include/other/global.hpp"
#include "../../include/other/const.hpp"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gMainFont = nullptr;
TTF_Font *gTitleFont = nullptr;
SDL_FRect gTileClips[kTotalTileSprites];
float gDeltaTime;