#include "tile.hpp"
#include "../other/const.hpp"
#include "../other/global.hpp"
#include "../other/util.hpp"

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