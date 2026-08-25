#include "../../include/scene/menuScene.hpp"

bool MenuScene::enter() {
    std::string path = "assets/maps/level1.map";
    mMapWidth = 304;
    mMapHeight = 160;
    mPlayerTexture.loadFromFile("assets/images/player.png");
    mTileTexture.loadFromFile("assets/images/tiles.png");
    player.setPlayer(32, 32);
    setTiles(mTiles, mMapWidth, path);
    return true;
}
    
bool MenuScene::exit() {
    mTiles.clear();
    mPlayerTexture.destroy();
    mTileTexture.destroy();
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {
    player.handleEvent(event);
}

void MenuScene::logic() {
    player.move();
    player.setCamera(mCamera, kScreenWidth, kScreenHeight);
}

void MenuScene::render() {
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);

    player.render(mCamera, mTiles, mPlayerTexture);
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;