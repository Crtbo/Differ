#include "../../include/engine/tile.hpp"
#include "../../include/other/const.hpp"
#include "../../include/other/detect.hpp"
#include "../../include/other/global.hpp"
#include <fstream>

Tile::Tile(int x, int y, int tileType) {
    mBox.x = x;
    mBox.y = y;
    mBox.w = kTileWidth;
    mBox.h = kTileHeight;
    mType = tileType;
}

void Tile::render(SDL_FRect &camera, Texture &texture) {
    if (checkCollision(camera, mBox))
        texture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
}

int Tile::getType() {
    return mType;
}

SDL_FRect Tile::getBox() {
    return mBox;
}

void setTiles(std::vector <Tile> &tiles, int mapWidth, std::string path) {
    std::ifstream map(path);
    tiles.clear();
    int x = 0, y = 0;
    int tileType;
    
    while (map >> tileType) {
        tiles.emplace_back(x, y, tileType);

        x += kTileWidth;
        if (x >= mapWidth) {
            x = 0;
            y += kTileHeight;
        }
    }

    gTileClips[kTileAir] = {0, 0, kTileWidth, kTileHeight};
    gTileClips[kTileLand] = {kTileWidth, 0, kTileWidth, kTileHeight};  
    map.close();
}

void saveTiles(std::vector <Tile> &tiles, std::string path) {
    std::ofstream map(path);

    for (int i = 0; i < tiles.size(); i++)
        map << tiles[i].getType() << " ";
    
    map.close();
}