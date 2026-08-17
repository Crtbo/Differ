#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Texture
{
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;

public:
    Texture();
    bool loadFromFile(std::string);
    bool loadFromRenderedText(std::string, SDL_Color, TTF_Font *);
    void destroy();
    void render(float, float, SDL_FRect *clip = nullptr);
    int getWidth();
    int getHeight();
    bool isLoaded();
};