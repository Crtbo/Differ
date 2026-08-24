#include "../../include/scene/menuScene.hpp"

bool MenuScene::enter() {
    std::string path = "assets/maps/level1.map";
    mapWidth = 304;
    mapHeight = 160;
    mTileTexture.loadFromFile("assets/images/tiles.png");
    setTiles(tiles, mapWidth, path);
    return true;
}
    
bool MenuScene::exit() {
    tiles.clear();
    mTileTexture.destroy();
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {}

void MenuScene::logic() {
    SDL_Log("Hello: %d", tiles.size());
}

void MenuScene::render() {
    for (int i = 0; i < tiles.size(); i++)
        tiles[i].render(camera, mTileTexture);
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;