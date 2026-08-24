#include "player.hpp"
#include "../other/util.hpp"

void Player::handleEvent(SDL_Event &e)
{

}

void Player::move(int width, int height)
{
   
}

void Player::setPlayer(int x, int y)
{
    mPos = {x, y};
    mVel = 3;
}

void Player::setCamera(SDL_FRect &camera, int width, int height)
{
    camera.x = (int)(mPosX + kPlayerWidth / 2 - kScreenWidth / 2);
    camera.y = (int)(mPosY + kPlayerHeight / 2 - kScreenHeight / 2);

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