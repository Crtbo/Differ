#include "../../include/engine/player.hpp"
#include "../../include/other/detect.hpp"

void Player::handleEvent(SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_LEFT:
            case SDLK_A: mVel -= 1; break;
            case SDLK_RIGHT:
            case SDLK_D: mVel += 1; break;
        }
    } else if (event.type == SDL_EVENT_KEY_UP && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_LEFT:
            case SDLK_A: mVel += 1; break;
            case SDLK_RIGHT:
            case SDLK_D: mVel -= 1; break;
        }
    }
}

void Player::move(std::vector <Tile> &tiles)
{
    if (!checkSurface(mHitBox, tiles))
    {
        mPos.y += 1;
        updateBox();
    }

    mPos.x += mVel;
    updateBox();
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

void Player::render(SDL_FRect &camera, std::vector <Tile> &tiles, Texture &texture)
{
    texture.render((int)mPos.x - camera.x, (int)mPos.y - camera.y);
}