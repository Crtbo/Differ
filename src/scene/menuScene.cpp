#include "../../include/scene/menuScene.hpp"

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

bool MenuScene::enter() {
    return true;
}
    
bool MenuScene::exit() {
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {}

void MenuScene::logic() {}

void MenuScene::render() {}

MenuScene MenuScene::sMenuScene;