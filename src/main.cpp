#include "../include/other/const.hpp"
#include "../include/other/global.hpp"
#include "../include/other/timer.hpp"
#include "../include/scene/exitScene.hpp"
#include "../include/scene/menuScene.hpp"
#include <SDL3_image/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
    srand(time(nullptr));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("unnamed game", kScreenWidth * 5, kScreenHeight * 5, 0, &gWindow, &gRenderer);
    SDL_SetRenderLogicalPresentation(gRenderer, kScreenWidth, kScreenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    TTF_Init();
    std::string fontPath{"assets/fonts/PixelOperator-Bold.ttf"};
    gMainFont = TTF_OpenFont(fontPath.c_str(), 27);
    gTitleFont = TTF_OpenFont(fontPath.c_str(), 36);
    SDL_Event event;
    SDL_zero(event);
    Timer capTimer;

    Uint64 lastTick = 0;
    Uint64 currentTick = 0;
    
    gCurrentScene = MenuScene::get();
    if (gCurrentScene->enter() == false) {
        gCurrentScene->exit();
        gCurrentScene = ExitScene::get();
    }

    while (gCurrentScene != ExitScene::get()) {
        capTimer.start();

        while (SDL_PollEvent(&event) == true) {
            gCurrentScene->handleEvent(event);

            if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
                setNextScene(ExitScene::get());
        }

        lastTick = currentTick;
        currentTick = SDL_GetTicks();
        gDeltaTime = (currentTick - lastTick) / 1000.0f;

        if (gDeltaTime > (float)1 / 30)
            gDeltaTime = (float)1 / 30;
        
        gCurrentScene->logic();

        if (changeScene() == false) {
            gCurrentScene->exit();
            gCurrentScene = ExitScene::get();
        }
        
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        gCurrentScene->render();
        SDL_RenderPresent(gRenderer);

        constexpr Uint64 nsPerFrame = 1000000000 / kScreenFps; 
        Uint64 frameNs = capTimer.getTicksNS();
        if (frameNs < nsPerFrame) SDL_DelayNS(nsPerFrame - frameNs);
    }

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
    return 0;
}
