#include "../../include/engine/texture.hpp"
#include "../../include/other/global.hpp"
#include <SDL3_image/SDL_image.h>

Texture::Texture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

bool Texture::loadFromFile(std::string path) {
    destroy();

    if (SDL_Surface *loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr)
        SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
    else {
        if (SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0xFF, 0x00, 0xFF)) == false)
            SDL_Log("Unable to color key! SDL error: %s", SDL_GetError());
        else {
            if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr)
                SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
            else {
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
                SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);
            }
        }

        SDL_DestroySurface(loadedSurface);
    }

    return mTexture != nullptr;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font) {
    destroy();

    if (SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textureText.length(), textColor); textSurface == nullptr)
        SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
    else {
        if (mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface); mTexture == nullptr)
            SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
            SDL_SetTextureScaleMode(mTexture, SDL_SCALEMODE_NEAREST);
        }

        SDL_DestroySurface(textSurface);
    }
    
    return mTexture != nullptr;
}

void Texture::destroy() {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void Texture::render(float x, float y, SDL_FRect *clip) {
    SDL_FRect dstRect = {x, y, (float)mWidth, (float)mHeight};
    
    if (clip != nullptr)
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    SDL_RenderTexture(gRenderer, mTexture, clip, &dstRect);
}

int Texture::getWidth() {
    return mWidth;
}

int Texture::getHeight() {
    return mHeight;
}

bool Texture::isLoaded() {
    return mTexture != nullptr;
}