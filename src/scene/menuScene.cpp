#include "../../include/scene/menuScene.hpp"

bool MenuScene::enter() {
    std::string path = "assets/maps/level1.map";
    mMapWidth = 304;
    mMapHeight = 160;
    mTileTexture.loadFromFile("assets/images/tiles.png");
    setTiles(mTiles, mMapWidth, path);
    return true;
}
    
bool MenuScene::exit() {
    mTiles.clear();
    mTileTexture.destroy();
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {}

void MenuScene::logic() {

}

void MenuScene::render() {
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;