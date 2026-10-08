#include "../../include/scene/exitScene.hpp"
#include "../../include/other/global.hpp"

ExitScene::ExitScene() {}

ExitScene *ExitScene::get() {
    return &sExitScene;
}

bool ExitScene::enter() {
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
    return true;
}
    
bool ExitScene::exit() {
    return true;
}

void ExitScene::handleEvent(SDL_Event &event) {}

void ExitScene::logic() {}

void ExitScene::render() {}

ExitScene ExitScene::sExitScene;