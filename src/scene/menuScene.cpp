#include "../../include/scene/menuScene.hpp"
#include "../../include/scene/editScene.hpp"
#include "../../include/other/global.hpp"
#include <sstream>

bool MenuScene::enter() {
    std::string path = "assets/maps/test.map";
    mMapWidth = 976;
    mMapHeight = 320;
    mPlayerTexture.loadFromFile("assets/images/player.png");
    mTileTexture.loadFromFile("assets/images/tiles.png");
    player.setPos(32, 64);
    player.setVel(0, 0);
    player.setBox(mPlayerTexture.getWidth(), mPlayerTexture.getHeight());
    setTiles(mTiles, mMapWidth, path);
    return true;
}
    
bool MenuScene::exit() {
    mTiles.clear();
    mPlayerTexture.destroy();
    mTileTexture.destroy();
    mDebugTexture.destroy();
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {
    player.handleEvent(event);

    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_E)
        setNextScene(EditScene::get());
}

void MenuScene::logic() {
    player.move(mTiles);
    player.setCamera(mCamera, mMapWidth, mMapHeight);

    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    std::stringstream text;
    text.str(""); text << "Can jump: " << player.canJump(); 
    mDebugTexture.loadFromRenderedText(text.str().c_str(), textColor, gMainFont);
}

void MenuScene::render() {
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);

    player.render(mCamera, mPlayerTexture);
    mDebugTexture.render(0, 0);
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;
