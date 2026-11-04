#include "../../include/engine/tile.hpp"
#include "../../include/other/const.hpp"
#include "../../include/other/detect.hpp"
#include "../../include/other/global.hpp"
#include <fstream>

Tile::Tile(int x, int y, int tileType) {
    mBox.x = x;
    mBox.y = y;
    mBox.w = kTileSize;
    mBox.h = kTileSize;
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

void Tile::setType(int type) {
    mType = type;
}

void setTiles(std::vector <Tile> &tiles, int mapWidth, int mapHeight, std::string path) {
    tiles.clear();
    int x = 0, y = 0;
    int tileType;
    
    if (!path.empty()) { 
        std::ifstream map(path);

        while (map >> tileType) {
            tiles.emplace_back(x, y, tileType);

            x += kTileSize;
            if (x >= mapWidth) {
                x = 0;
                y += kTileSize;
            }
        }

        map.close();
    } else {
        while (y < mapHeight) {
            tiles.emplace_back(x, y, kTilePlacehold);

            x += kTileSize;
            if (x >= mapWidth) {
                x = 0;
                y += kTileSize;
            }
        }
    }

    gTileClips[kTilePlacehold] = {0, 0, kTileSize, kTileSize};
    gTileClips[kTileAir] = {kTileSize, 0, kTileSize, kTileSize};
    gTileClips[kTileSpecial] = {kTileSize * 2, 0, kTileSize, kTileSize}; 
    gTileClips[kTileUpLeft] = {0, kTileSize, kTileSize, kTileSize}; 
    gTileClips[kTileUpMid] = {kTileSize, kTileSize, kTileSize, kTileSize}; 
    gTileClips[kTileUpRight] = {kTileSize * 2, kTileSize, kTileSize, kTileSize}; 
    gTileClips[kTileMidLeft] = {0, kTileSize * 2, kTileSize, kTileSize}; 
    gTileClips[kTileMidMid] = {kTileSize, kTileSize * 2, kTileSize, kTileSize}; 
    gTileClips[kTileMidRight] = {kTileSize * 2, kTileSize * 2, kTileSize, kTileSize};
    gTileClips[kTileDownleft] = {0, kTileSize * 3, kTileSize, kTileSize};
    gTileClips[kTileDownMid] = {kTileSize, kTileSize * 3, kTileSize, kTileSize};
    gTileClips[kTileDownRight] = {kTileSize * 2, kTileSize * 3, kTileSize, kTileSize};
}

void saveTiles(std::vector <Tile> tiles, int mapWidth, std::string path) {
    std::ofstream map(path);

    for (int i = 0; i < tiles.size(); i++) {
        map << tiles[i].getType() << " ";

        if ((i + 1) % (mapWidth / kTileSize) == 0)
            map << '\n';
    }
        
    map.close();
}

void placeTile(std::vector <Tile> &tiles, SDL_Point cursor, SDL_FRect camera, int tileType) {
    SDL_FRect box = {cursor.x + camera.x, cursor.y + camera.y, 0, 0};

    for (int i = 0; i < tiles.size(); i++)
        if (checkCollision(box, tiles[i].getBox())) {
            tiles[i].setType(tileType);
            break;
        }
}