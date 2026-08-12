#include "../../include/scene/exitScene.hpp"

ExitScene::ExitScene() {}

ExitScene *ExitScene::get() {
    return &sExitScene;
}

bool ExitScene::enter() {
    return true;
}
    
bool ExitScene::exit() {
    return true;
}

void ExitScene::handleEvent(SDL_Event &event) {}

void ExitScene::logic() {}

void ExitScene::render() {}

ExitScene ExitScene::sExitScene;