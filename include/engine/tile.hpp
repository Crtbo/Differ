#pragma once
#include "texture.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class Tile {
    SDL_FRect mBox;
    int mType;

public:
    Tile(int x, int y, int tileType);
    void render(SDL_FRect &camera, Texture &texture);
    int getType();
    SDL_FRect getBox();
};

void setTiles(std::vector <Tile> &tiles, int mapWidth, std::string path);