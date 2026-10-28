#include "../../include/scene/levelScene.hpp"
#include "../../include/scene/menuScene.hpp"
#include "../../include/other/global.hpp"
#include <sstream>

bool LevelScene::enter() {
    std::string path = "assets/maps/test.map";
    mMapWidth = 61 * kTileSize;
    mMapHeight = 50 * kTileSize;
    mPlayerTexture.loadFromFile("assets/images/player.png");
    mTileTexture.loadFromFile("assets/images/tiles.png");
    player.setPos(32, 64);
    player.setVel(0, 0);
    player.setBox(mPlayerTexture.getWidth(), mPlayerTexture.getHeight());
    setTiles(mTiles, mMapWidth, mMapHeight, path);
    return true;
}
    
bool LevelScene::exit() {
    mTiles.clear();
    mPlayerTexture.destroy();
    mTileTexture.destroy();
    mDebugTextTexture.destroy();
    return true;
}

void LevelScene::handleEvent(SDL_Event &event) {
    player.handleEvent(event);

    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0)
        if (event.key.key == SDLK_BACKSPACE)
            setNextScene(MenuScene::get());
}

void LevelScene::logic() {
    player.move(mTiles);
    player.setCamera(mCamera, mMapWidth, mMapHeight);

    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    std::stringstream text;
    text.str(""); text << "Can jump: " << player.canJump(); 
    mDebugTextTexture.loadFromRenderedText(text.str().c_str(), textColor, gMainFont);
}

void LevelScene::render() {
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);

    player.render(mCamera, mPlayerTexture);
    mDebugTextTexture.render(0, 0);
}

LevelScene::LevelScene() {}

LevelScene *LevelScene::get() {
    return &sLevelScene;
}

LevelScene LevelScene::sLevelScene;
