#include "../../include/scene/editScene.hpp"

EditScene::EditScene() {}

EditScene *EditScene::get() {
    return &sEditScene;
}

bool EditScene::enter() {
    return true;
}
    
bool EditScene::exit() {
    return true;
}

void EditScene::handleEvent(SDL_Event &event) {}

void EditScene::logic() {}

void EditScene::render() {}

EditScene EditScene::sEditScene;