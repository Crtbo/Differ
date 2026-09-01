#include "../../include/scene/menuScene.hpp"

bool MenuScene::enter() {
    std::string path = "assets/maps/level1.map";
    mMapWidth = 304;
    mMapHeight = 160;
    mPlayerTexture.loadFromFile("assets/images/player.png");
    mTileTexture.loadFromFile("assets/images/tiles.png");
    player.setPos(32, 32);
    player.setVel(0, 0);
    player.setBox(mPlayerTexture.getWidth(), mPlayerTexture.getHeight());
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
    player.move(mTiles);
    player.setCamera(mCamera, kScreenWidth, kScreenHeight);
}

void MenuScene::render() {
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);

    player.render(mCamera, mPlayerTexture);
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;