#pragma once
#include "../engine/tile.hpp"
#include <SDL3/SDL.h>
#include <vector>

bool checkCollision(SDL_FRect, SDL_FRect);
bool checkSurface(SDL_FRect, std::vector <Tile> &);