#include "../../include/other/util.hpp"
#include "../../include/other/const.hpp"
#include "../../include/other/global.hpp"
#include <SDL3_image/SDL_image.h>
#include <string>

void initiate() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("unnamed game", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer);
    TTF_Init();

    std::string fontPath{"assets/fonts/PixelOperator-Bold.ttf"};
    gMainFont = TTF_OpenFont(fontPath.c_str(), 27);
    gTitleFont = TTF_OpenFont(fontPath.c_str(), 36);
}

void close() {
    TTF_CloseFont(gMainFont);
    gMainFont = nullptr;
    TTF_CloseFont(gTitleFont);
    gTitleFont = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}