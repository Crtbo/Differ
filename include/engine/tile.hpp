#pragma once
#include "texture.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class Tile {
    private:
        SDL_FRect mBox;
        int mType;

    public:
        Tile(int, int, int);
        void render(SDL_FRect &, Texture &);
        int getType();
        SDL_FRect getBox();
        void setType(int);
};

void setTiles(std::vector <Tile> &, int, std::string);
void saveTiles(std::vector <Tile>, std::string);
void placeTile(std::vector <Tile> &, SDL_Point, SDL_Rect, int);