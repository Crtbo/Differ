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
    SDL_CreateWindowAndRenderer("DIFFER", kScreenWidth * kScale, kScreenHeight * kScale, 0, &gWindow, &gRenderer);
    SDL_SetRenderLogicalPresentation(gRenderer, kScreenWidth, kScreenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    SDL_SetRenderVSync(gRenderer, 1);
    TTF_Init();
    SDL_HideCursor();
    std::string fontPath{"assets/fonts/PixelOperator-Bold.ttf"};
    gMainFont = TTF_OpenFont(fontPath.c_str(), 27);
    gTitleFont = TTF_OpenFont(fontPath.c_str(), 36);
    SDL_Event event;
    SDL_zero(event);
    Timer capTimer;

    int lastTick = 0;
    int currentTick = 0;
    const float capDelta = 1.f / 30;
    
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
        gDeltaTime = (currentTick - lastTick) / 1000.f;

        if (gDeltaTime > capDelta)
            gDeltaTime = capDelta;
        
        gCurrentScene->logic();

        if (changeScene() == false) {
            gCurrentScene->exit();
            gCurrentScene = ExitScene::get();
        }
        
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);
        gCurrentScene->render();
        SDL_RenderPresent(gRenderer);

        constexpr Uint64 nsPerFrame = 1000000000 / kScreenFps; 
        Uint64 frameNs = capTimer.getTicksNS();
        if (frameNs < nsPerFrame) SDL_DelayNS(nsPerFrame - frameNs);
    }
    return 0;
}
