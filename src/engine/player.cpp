#include "../../include/engine/player.hpp"
#include "../../include/other/detect.hpp"
#include "../../include/other/global.hpp"

void Player::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_A: mVel -= 1; break;
            case SDLK_D: mVel += 1; break;
            case SDLK_SPACE: 
                mPos.y -= 32; 
                updateBox(); 
                break;
        }
    } else if (event.type == SDL_EVENT_KEY_UP && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_A: mVel += 1; break;
            case SDLK_D: mVel -= 1; break;
        }
    }
}

void Player::move(std::vector <Tile> &tiles)
{
    mPos.y += 1;
    updateBox();
    if (checkSurface(mFeetBox, tiles)) {
        mPos.y -= 1;
        updateBox();
    }

    mPos.x += mVel;
    updateBox();
    if (checkSurface(mHitBox, tiles)) {
        mPos.x -= mVel;
        updateBox();
    }
}

void Player::render(SDL_FRect &camera, std::vector <Tile> &tiles, Texture &texture)
{
    texture.render((int)mPos.x - camera.x, (int)mPos.y - camera.y);
    // SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    // SDL_RenderRect(gRenderer, &mHitBox);
    // SDL_RenderRect(gRenderer, &mFeetBox);
}

void Player::setCamera(SDL_FRect &camera, int width, int height)
{
    camera.x = (int)(mPos.x / 2 - kScreenWidth / 2);
    camera.y = (int)(mPos.y / 2 - kScreenHeight / 2);

    if (camera.x < 0)
        camera.x = 0;
    else if (camera.x + camera.w > width)
        camera.x = width - camera.w;
    if (camera.y < 0)
        camera.y = 0;
    else if (camera.y + camera.h > height)
        camera.y = height - camera.h;
}

void Player::setBox(float w, float h) {
    mHitBox.w = w;
    mHitBox.h = h;
    mFeetBox.w = w;
    mFeetBox.h = 4;
    updateBox();
}

void Player::updateBox() {
    mHitBox.x = mPos.x;
    mHitBox.y = mPos.y;
    mFeetBox.x = mPos.x;
    mFeetBox.y = mPos.y + mHitBox.h - 4;
}