#include "../include/other/const.hpp"
#include "../include/other/global.hpp"
#include "../include/other/timer.hpp"
#include "../include/other/util.hpp"
#include "../include/scene/exitScene.hpp"
#include "../include/scene/menuScene.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(nullptr));
    initiate();
    SDL_Event event;
    SDL_zero(event);
    Timer capTimer;
    
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

    close();
    return 0;
}
