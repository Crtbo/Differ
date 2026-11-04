#include "../../include/other/detect.hpp"
#include "../../include/other/const.hpp"

bool checkCollision(SDL_FRect a, SDL_FRect b)
{
    int leftA = a.x, leftB = b.x;
    int rightA = a.x + a.w, rightB = b.x + b.w;
    int topA = a.y, topB = b.y;
    int bottomA = a.y + a.h, bottomB = b.y + b.h;

    if (bottomA <= topB) return false;
    if (topA >= bottomB) return false;
    if (rightA <= leftB) return false;
    if (leftA >= rightB) return false;

    return true;
}

int checkSurface(SDL_FRect box, std::vector <Tile> &tiles)
{
    for (int i = 0; i < tiles.size(); i++)
        if (tiles[i].getType() <= kTileSpecial)
            if (checkCollision(box, tiles[i].getBox()))
                return i;
    return -1;
}