#pragma once
#include "object.hpp"
#include "tile.hpp"
#include "../other/const.hpp"
#include <vector>

class Player : public Object
{
    public:
        void handleEvent(SDL_Event &);
        void move();
        void setPlayer(float, float);
        void setCamera(SDL_FRect &, int, int);
        void render(SDL_FRect &, std::vector <Tile> &, Texture &);
};